#include <stddef.h>
#include <string.h>

#include "usb.h"
#include "usb_descriptor.h"

// zero when we are not configured, non-zero when enumerated
static volatile uint8_t usb_configuration = 0;

uint8_t keyboard_data[8];
static uint8_t keyboard_protocol = 1;
static uint8_t keyboard_idle_config = 125;
volatile uint8_t keyboard_leds = 0;

void USB_Init() {
    // Global Interrupt Disable
    cli();
    // Enable USB
    HW_CONFIG();
    // Unfreeze the clock
    USB_FREEZE();
    // Config PLL
    PLL_CONFIG();
    // Wait for PLL is ready
    while (!(PLLCSR & (1 << PLOCK))) ;
    // Start USB clock
    USB_CONFIG();
    // Disable watchdog if enabled by bootloader/fuses
    MCUSR &= ~(1 << WDRF);
    // Full speed mode
    UDCON = 0;
    // Re-enable the EORSTE (End Of Reset) Interrupt so we
    // know when we can configure the control endpoint
    UDIEN = (1 << EORSTE) | (1 << SOFE);
    // Global Interrupt Enable
    sei();
}

void usb_remote_wakeup() {
    if (UDINT & (1 << SUSPI)) {
        UDCON |= 1 << RMWKUP;
    }
}

void clear_key(uint8_t key) {
    if (key > 0) {
        if (key >= 0xe0 && key < 0xe8) {
            keyboard_data[0] &= ~(1 << (key - 0xe0));
        }

        uint8_t i = 8;

        while (i > 2) {
            i--;

            if (keyboard_data[i] == key) {
                if (i < 7) {
                    memmove(keyboard_data + i, keyboard_data + i + 1, 7 - i);
                }

                keyboard_data[7] = 0;
            }
        }
    }
}

void press_key(uint8_t key) {
    if (key >= 0xe0 && key < 0xe8) {
        keyboard_data[0] |= 1 << (key - 0xe0);
    } else if (key > 0) {
        clear_key(key);
        memmove(keyboard_data + 3, keyboard_data + 2, 5);
        keyboard_data[2] = key;
    }

    keyboard_data[1] = 0;
}

void release_all_keys() {
    memset(keyboard_data + 2, 0, 6);
}

void release_key(uint8_t key) {
    clear_key(key);
    keyboard_data[1] = 0;
}

int8_t usb_send(uint8_t ep, uint8_t const *ptr, int len) {
    uint8_t i, intr_state, timeout;

    if (!usb_configuration) return -1;
    intr_state = SREG;

    usb_remote_wakeup();

    cli();
    UENUM = ep;
    timeout = UDFNUML + 50;
    while (1) {
        // are we ready to transmit?
        if (UEINTX & (1 << RWAL)) break;
        SREG = intr_state;
        // has the USB gone offline?
        if (!usb_configuration) return -1;
        // have we waited too long?
        if (UDFNUML == timeout) return -1;
        // get ready to try checking again
        intr_state = SREG;
        cli();
        UENUM = ep;
    }
    for (i = 0; i < len; i++) {
        UEDATX = ptr[i];
    }
    UEINTX = 0x3a;
    SREG = intr_state;
    return 0;
}

int8_t usb_keyboard_send() {
    return usb_send(0x03, keyboard_data, 8);
}

static inline void usb_wait_in_ready() {
    while (!(UEINTX & (1 << TXINI))) ;
}

static inline void usb_send_in() {
    UEINTX = ~(1 << TXINI);
}

static inline void usb_wait_receive_out() {
    while (!(UEINTX & (1 << RXOUTI))) ;
}

static inline void usb_ack_out() {
    UEINTX = ~(1 << RXOUTI);
}

static inline uint8_t Endpoint_IsSETUPReceived() {
    return ((UEINTX & (1 << RXSTPI)) ? 1 : 0);
}

static inline uint8_t Endpoint_IsStalled() {
    return ((UECONX & (1 << STALLRQ)) ? 1 : 0);
}

static inline uint8_t Endpoint_Read_8() {
    return UEDATX;
}

static inline void USB_Device_SetDeviceAddress(const uint8_t Address) {
    UDADDR = Address | (1 << ADDEN);
}

static inline void Endpoint_ClearIN() {
    UEINTX &= ~(1 << TXINI);
}

static inline void Endpoint_ClearOUT() {
    UEINTX &= ~(1 << RXOUTI);
}

static inline void Endpoint_ClearSETUP() {
    UEINTX &= ~(1 << RXSTPI);
}

static inline void Endpoint_StallTransaction() {
    UECONX |= (1 << STALLRQ);
}

static inline void Endpoint_DisableEndpoint() {
    UECONX &= ~(1 << EPEN);
}

static inline void Endpoint_EnableEndpoint() {
    UECONX |= (1 << EPEN);
}

static inline void Endpoint_Write_8(const uint8_t Data) {
    UEDATX = Data;
}

static inline void Endpoint_ResetEndpoint(const uint8_t Address) {
    UERST = (1 << (Address & ENDPOINT_EPNUM_MASK));
    UERST = 0;
}

static inline void Endpoint_SelectEndpoint(const uint8_t Address) {
    UENUM = (Address & ENDPOINT_EPNUM_MASK);
}

ISR(USB_GEN_vect) {
    general_isr();
}

void general_isr() {
    if (UDINT & (1 << EORSTI))
        configureEndpoint();
    UDINT = 0;
}

void configureEndpoint() {
    // select endpoint 0
    UENUM = 0;
    // enable endpoint 0
    UECONX = (1 << EPEN);
    // endpoint 0 is a control endpoint
    UECFG0X = 0;
    // endpoint 0: 64 bytes, one bank, allocate mem
    UECFG1X = (1 << EPSIZE1) | (1 << EPSIZE0) | (1 << ALLOC);
    UEINTX = 0;
    UEIENX = (1 << RXSTPE);

    usb_configuration = 0;
}

ISR(USB_COM_vect) {
    UENUM = 0;
    if (Endpoint_IsSETUPReceived()) {
        uint8_t rtype = UEDATX;
        uint8_t request = UEDATX;
        uint16_t value = UEDATX;
        value |= (UEDATX << 8);
        uint16_t index = UEDATX;
        index |= (UEDATX << 8);
        uint16_t length = UEDATX;
        length |= (UEDATX << 8);

        // UEINTX = ~((1 << RXSTPI) | (1 << RXOUTI) | (1 << TXINI));

        // Handshake the Interrupts, do this after recording
        // the packet because it also clears the endpoint banks
        UEINTX &= ~(
            (1 << RXSTPI) | (1 << RXOUTI) |
            (1 << TXINI));

        if (request == GET_DESCRIPTOR) {
            uint8_t const *desc_addr = NULL;
            uint8_t desc_length = 0;
            uint8_t const *p = (uint8_t const *)descriptor_list;
            for (uint8_t i = 0; i < NUM_DESC_LIST; i++) {
                if (pgm_read_word(p) == value && pgm_read_word(p + 2) == index) {
                    desc_addr = (uint8_t const *)pgm_read_word(p + 4);
                    desc_length = pgm_read_byte(p + 6);
                    break;
                }
                p += sizeof(struct descriptor_list_struct);
            }
            if (!desc_addr) {
                UECONX = (1 << STALLRQ) | (1 << EPEN);  //stall
                return;
            }
            uint8_t len = (length < 255) ? length : 255;
            if (len > desc_length) len = desc_length;
            uint8_t n;
            do {
                // wait for host ready for IN packet
                uint8_t i;
                do {
                    i = UEINTX;
                } while (!(i & ((1 << TXINI) | (1 << RXOUTI))));
                if (i & (1 << RXOUTI)) return;  // abort
                // send IN packet
                n = len < ENDPOINT0_SIZE ? len : ENDPOINT0_SIZE;
                for (uint8_t i = 0; i < n; i++) {
                    UEDATX = pgm_read_byte(desc_addr++);
                }
                len -= n;
                usb_send_in();
            } while (len || n == ENDPOINT0_SIZE);
            return;
        }
        if (request == SET_ADDRESS) {
            set_address(value);
            return;
        }
        if (request == SET_CONFIGURATION) {
            if (rtype == 0) {
                set_configuration(value);
                return;
            }
        }
        if (request == GET_CONFIGURATION) {
            if (rtype == 0x80) {
                get_configuration(usb_configuration);
                return;
            }
        }
        if (request == GET_STATUS) {
            get_status(index);
            return;
        }
        // if (request == CLEAR_FEATURE || request == SET_FEATURE) {
        //  if (rtype == 0x02 && value == 0) {
        //      uint8_t i = index & 0x7f;
        //      if (i >= 1 && i <= MAX_ENDPOINT) {
        //          usb_send_in();
        //          UENUM = i;
        //          if (request == SET_FEATURE) {
        //              UECONX = (1 << STALLRQ) | (1 << EPEN);
        //          } else {
        //              UECONX = (1 << STALLRQC) | (1 << RSTDT) | (1 << EPEN);
        //              UERST = (1 << i);
        //              UERST = 0;
        //          }
        //          return;
        //      }
        //  }
        // }
        // Is this a request to the keyboard interface for HID
        if (index == 0x00) {
            if (rtype == 0xa1) {
                if (request == HID_GET_IDLE) {
                    usb_wait_in_ready();
                    UEDATX = keyboard_idle_config;
                    usb_send_in();
                    return;
                }
                if (request == HID_GET_PROTOCOL) {
                    usb_wait_in_ready();
                    UEDATX = keyboard_protocol;
                    usb_send_in();
                    return;
                }
            }
            if (rtype == 0x21) {
                if (request == HID_SET_REPORT) {
                    usb_wait_receive_out();
                    keyboard_leds = UEDATX;
                    usb_ack_out();
                    usb_send_in();
                    return;
                }
                if (request == HID_SET_IDLE) {
                    keyboard_idle_config = (value >> 8);
                    usb_send_in();
                    return;
                }
                if (request == HID_SET_PROTOCOL) {
                    keyboard_protocol = value;
                    usb_send_in();
                    return;
                }
            }
        }
    }

    Endpoint_ClearIN();
    Endpoint_ClearOUT();
    Endpoint_ClearSETUP();
    Endpoint_StallTransaction();
    Endpoint_DisableEndpoint();
}

void set_address(uint8_t value) {
    usb_send_in();
    usb_wait_in_ready();
    USB_Device_SetDeviceAddress(value);
}

void get_status(uint8_t index) {
    usb_wait_in_ready();
    uint8_t EndpointIndex = (index & ENDPOINT_EPNUM_MASK);
    Endpoint_SelectEndpoint(EndpointIndex);
    Endpoint_Write_8(Endpoint_IsStalled());
    usb_send_in();
}

// GET_CONFIGURATION is the host trying to get
// the current config status of the device.
void get_configuration(uint8_t value) {
    usb_wait_in_ready();
    Endpoint_Write_8(value);
    usb_send_in();
}

// Refer to USB Spec 9.4.7 - This is the configuration request
// to place the device into address mode
void set_configuration(uint8_t value) {
    usb_configuration = value;
    usb_send_in();
    // Select Endpoint
    UENUM = KEYBOARD_ENDPOINT_NUM;
    Endpoint_EnableEndpoint();
    // Set Endpoint Direction
    UECFG0X = EP_TYPE_INTERRUPT_IN;
    // Dual Bank Endpoint, 8 Bytes, allocate memory
    UECFG1X = EP_DOUBLE_BUFFER;
    Endpoint_ResetEndpoint(value);
}
