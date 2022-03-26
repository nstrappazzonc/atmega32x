#include "usb.h"
#include "usb_descriptor.h"

static inline void usb_wait_in_ready() {
    while (!(UEINTX & (1 << TXINI))) ;
}

static inline void usb_send_in() {
    UEINTX = ~(1 << TXINI);
}

static inline uint8_t Endpoint_IsSETUPReceived() {
    return ((UEINTX & (1 << RXSTPI)) ? 1 : 0);
}

void USBInit() {
    HW_CONFIG();
    // Enable USB
    USB_FREEZE();
    // Config PLL
    PLL_CONFIG();
    // Wait for PLL lock
    while (!(PLLCSR & (1 << PLOCK)));
    // Start USB clock
    USB_CONFIG();
    // Enable attach resistor
    UDCON = 0;
    UDIEN = (1 << EORSTE) | (1 << SOFE);
    STATUS = STATUS_IDLE;
    sei();
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
}

ISR(USB_COM_vect) {
    processControlRequest();
}

void processControlRequest() {
    if (STATUS == STATUS_IDLE) {
        uint16_t value = UEDATX;
        UENUM = 0;
        if (Endpoint_IsSETUPReceived()) {
            switch (UEDATX) {
                case GET_DESCRIPTOR:
                    break;
                case SET_ADDRESS:
                    value |= (UEDATX << 8);
                    usb_send_in();
                    usb_wait_in_ready();
                    UDADDR = value | (1 << ADDEN);
                    break;
                case GET_STATUS:
                    break;
                case GET_CONFIGURATION:
                    break;
                case SET_CONFIGURATION:
                    usb_send_in();

                    break;
                default:
                    break;
            }
        }
    } else if (STATUS == STATUS_HALT) {
        UENUM = 0;
        Endpoint_ClearIN();
        Endpoint_ClearOUT();
        Endpoint_ClearSETUP();
        Endpoint_StallTransaction();
        Endpoint_DisableEndpoint();
    }
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
