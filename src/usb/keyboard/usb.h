#include <stdint.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>

void USB_Init();
void usb_remote_wakeup();

void clear_key(uint8_t);
void press_key(uint8_t);
void release_all_keys();
void release_key(uint8_t);
void get_status(uint8_t);
void set_address(uint8_t);
void get_configuration(uint8_t);
void set_configuration(uint8_t);

int8_t usb_keyboard_send();
extern uint8_t keyboard_data[8];
extern volatile uint8_t keyboard_leds;

#define EP_TYPE_CONTROL 0x00
#define EP_TYPE_BULK_IN 0x81
#define EP_TYPE_BULK_OUT 0x80
#define EP_TYPE_INTERRUPT_IN 0xc1
#define EP_TYPE_INTERRUPT_OUT 0xc0
#define EP_TYPE_ISOCHRONOUS_IN 0x41
#define EP_TYPE_ISOCHRONOUS_OUT 0x40

#define EP_SINGLE_BUFFER 0x02
#define EP_DOUBLE_BUFFER 0x06

#define EP_SIZE(s) ((s) == 64 ? 0x30 : ((s) == 32 ? 0x20 : ((s) == 16 ? 0x10 : 0x00)))

#define MAX_ENDPOINT 4
#define KEYBOARD_ENDPOINT_NUM 0x03  // The second endpoint is the HID endpoint

/** Endpoint number mask, for masking against endpoint addresses to retrieve the endpoint's
 *  numerical address in the device.
*/
#define ENDPOINT_EPNUM_MASK 0x0F

#define LSB(n) (n & 255)
#define MSB(n) ((n >> 8) & 255)

// ATmega32u2
#if defined(__AVR_ATmega32U2__)
#define HW_CONFIG()  (REGCR = 0x00)
#define PLL_CONFIG() (PLLCSR = 0x06)      // Controls USB interface clock 0x06 for 16MHz clock source, or 0x02 for 8MHz clock source
#define USB_CONFIG() (USBCON = (1<<USBE)) // No UPGPADE for the ATmega32u2
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
// ATmega32u4
#elif defined(__AVR_ATmega32U4__)
#define HW_CONFIG() (UHWCON = 0x01)
#define PLL_CONFIG() (PLLCSR = 0x12)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
// AT90USB162
#elif defined(__AVR_AT90USB162__)
#define HW_CONFIG()
#define PLL_CONFIG() (PLLCSR = ((1<<PLLE)|(1<<PLLP0)))
#define USB_CONFIG() (USBCON = (1<<USBE))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
// AT90USB646
#elif defined(__AVR_AT90USB646__)
#define HW_CONFIG() (UHWCON = 0x81)
#define PLL_CONFIG() (PLLCSR = 0x1A)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
// AT90USB1286
#elif defined(__AVR_AT90USB1286__)
#define HW_CONFIG() (UHWCON = 0x81)
#define PLL_CONFIG() (PLLCSR = 0x16)
#define USB_CONFIG() (USBCON = ((1<<USBE)|(1<<OTGPADE)))
#define USB_FREEZE() (USBCON = ((1<<USBE)|(1<<FRZCLK)))
#endif

// Standard control endpoint request types
#define GET_STATUS 0
#define CLEAR_FEATURE 1
#define SET_FEATURE 3
#define SET_ADDRESS 5
#define GET_DESCRIPTOR 0x06
#define GET_CONFIGURATION 8
#define SET_CONFIGURATION 9
#define GET_INTERFACE 10
#define SET_INTERFACE 11
// HID (human interface device)
#define HID_GET_REPORT 1
#define HID_GET_IDLE 2
#define HID_GET_PROTOCOL 3
#define HID_SET_REPORT 9
#define HID_SET_IDLE 10
#define HID_SET_PROTOCOL 11
// CDC (communication class device)
#define CDC_SET_LINE_CODING 0x20
#define CDC_GET_LINE_CODING 0x21
#define CDC_SET_CONTROL_LINE_STATE 0x22

void general_isr();
void configureEndpoint();

static inline void Endpoint_ClearIN();
static inline void Endpoint_ClearOUT();
static inline void Endpoint_ClearSETUP();
static inline void Endpoint_SelectEndpoint(uint8_t);
static inline void Endpoint_StallTransaction();
static inline void Endpoint_DisableEndpoint();
static inline uint8_t Endpoint_IsStalled();
static inline uint8_t Endpoint_IsSETUPReceived();
static inline uint8_t Endpoint_Read_8();
static inline void Endpoint_Write_8(uint8_t);
static inline void USB_Device_SetDeviceAddress(uint8_t);
