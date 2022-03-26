/*
 * vim: ts=4 nobackup
 */

#define VENDOR_ID        0x03A8
#define PRODUCT_ID       0x201d
#define STR_MANUFACTURER L"My Personal Keyboard"
#define STR_PRODUCT      L"MyPKB"
#define STR_SERIALNUMBER L"1"

#define ENDPOINT0_SIZE		     32
#define KEYBOARD_SIZE            8
#define KEYBOARD_BUFFER          EP_DOUBLE_BUFFER
#define KEYBOARD_HID_DESC_OFFSET (9 + 9)
#define KEYBOARD_HID_DESC_LENGTH (9 + 9 + 7)
#define NUM_DESC_LIST (sizeof(descriptor_list)/sizeof(struct descriptor_list_struct))

struct usb_string_descriptor_struct {
	uint8_t length;
	uint8_t descriptor_type;
	int16_t string[];
};

struct descriptor_list_struct {
	uint16_t value;
	uint16_t index;
	uint8_t const *addr;
	uint8_t length;
};

// Device descriptor:
PROGMEM static const uint8_t device_desc[] = {
	18,                               // Size
	1,                                // Descriptor type
	0x10, 0x01,                       // bcdUSB
	0,                                // Device class
	0,                                // Device subclass
	0,                                // Device protocol
	ENDPOINT0_SIZE,                   // Max packet size for EP0
	LSB(VENDOR_ID), MSB(VENDOR_ID),   // Vendor ID
	LSB(PRODUCT_ID), MSB(PRODUCT_ID), // Product ID
	0x00, 0x01,                       // bcdDevice
	1,                                // Index of string descriptor for manufacturer
	2,                                // Index of string descriptor for product
	3,                                // Index of string descriptor for serial number
	1                                 // Number of configurations
};

// Report descriptors:
PROGMEM static const uint8_t keyboard_hid_report_desc[] = {
	0x05, 0x01,          // Usage Page (Generic Desktop),
	0x09, 0x06,          // Usage (Keyboard),
	0xa1, 0x01,          // Collection (Application),
	0x05, 0x07,          //   Usage Page (Key Codes),
	0x19, 0xe0,          //   Usage Minimum (224),
	0x29, 0xe7,          //   Usage Maximum (231),
	0x15, 0x00,          //   Logical Minimum (0),
	0x25, 0x01,          //   Logical Maximum (1),
	0x95, 0x08,          //   Report Count (8),
	0x75, 0x01,          //   Report Size (1),
	0x81, 0x02,          //   Input (Data, Variable, Absolute), ;Modifier byte
	0x95, 0x01,          //   Report Count (1),
	0x75, 0x08,          //   Report Size (8),
	0x81, 0x01,          //   Input (Constant),                 ;Reserved byte
	0x05, 0x07,          //   Usage Page (Key Codes),
	0x19, 0x00,          //   Usage Minimum (0),
	0x29, 0xff,          //   Usage Maximum (255),
	0x15, 0x00,          //   Logical Minimum (0),
	0x26, 0xff, 0x00,    //   Logical Maximum(255),
	0x95, 0x06,          //   Report Count (6),
	0x75, 0x08,          //   Report Size (8),
	0x81, 0x00,          //   Input (Data, Array, Absolute),
	0x05, 0x08,          //   Usage Page (LEDs),
	0x19, 0x01,          //   Usage Minimum (1),
	0x29, 0x05,          //   Usage Maximum (5),
	0x95, 0x05,          //   Report Count (5),
	0x75, 0x01,          //   Report Size (1),
	0x91, 0x02,          //   Output (Data, Variable, Absolute, NonVolatile), ;LED report
	0x95, 0x01,          //   Report Count (1),
	0x75, 0x03,          //   Report Size (3),
	0x91, 0x01,          //   Output (Constant),                 ;LED report padding
	0xc0                 // End Collection
};

// Configuration descriptor:
PROGMEM const uint8_t config_desc[] = {
	9, // sizeof(usbDescriptorConfiguration): length of descriptor in bytes
	2, // descriptor type
	9 + KEYBOARD_HID_DESC_LENGTH, 0, // total length of data returned (including inlined descriptors)
	1, // number of interfaces in this configuration
	1, // index of this configuration
	0, // configuration name string index
	(1 << 7) | (1 << 5), // bus powered | remote wakeup
	100 / 2, // max USB current in 2mA units
	//// interface: keyboard
	// interface descriptor follows inline:
	9, // sizeof(usbDescrInterface): length of descriptor in bytes
	4, // descriptor type
	0, // index of this interface
	0, // alternate setting for this interface
	1, // endpoints excl 0: number of endpoint descriptors to follow
	3, // interface class
	1, // interface subclass
	1, // interface protocol
	0, // string index for interface
	9, // sizeof(usbDescrHID): length of descriptor in bytes
	0x21, // descriptor type: HID
	0x10, 0x01, // BCD representation of HID version
	0x00, // target country code
	0x01, // number of HID Report (or other HID class) Descriptor infos to follow
	0x22, // descriptor type: report
	sizeof(keyboard_hid_report_desc), 0, // total length of report descriptor
	7, // sizeof(usbDescrEndpoint)
	5, // descriptor type = endpoint
	3 | 0x80, // IN endpoint
	3, // attrib: Interrupt endpoint
	8, 0, // maximum packet size
	10, // in ms
};

// Strings descriptor:
PROGMEM static const struct usb_string_descriptor_struct string0 = {
	4,
	3,
	{0x0409}
};

PROGMEM static const struct usb_string_descriptor_struct string1 = {
	sizeof(STR_MANUFACTURER),
	3,
	STR_MANUFACTURER
};

PROGMEM static const struct usb_string_descriptor_struct string2 = {
	sizeof(STR_PRODUCT),
	3,
	STR_PRODUCT
};

PROGMEM static const struct usb_string_descriptor_struct string3 = {
	sizeof(STR_SERIALNUMBER),
	3,
	STR_SERIALNUMBER
};

// Descriptor list:
PROGMEM static const struct descriptor_list_struct descriptor_list[] = {
	{0x0100, 0x0000, device_desc, sizeof(device_desc)},
	{0x0200, 0x0000, config_desc, sizeof(config_desc)},
	{0x2200, 0x0000, keyboard_hid_report_desc, sizeof(keyboard_hid_report_desc)},
	{0x2100, 0x0000, config_desc + KEYBOARD_HID_DESC_OFFSET, 9},
	{0x0300, 0x0000, (uint8_t const *)&string0, 4},
	{0x0301, 0x0409, (uint8_t const *)&string1, sizeof(STR_MANUFACTURER)},
	{0x0302, 0x0409, (uint8_t const *)&string2, sizeof(STR_PRODUCT)},
	{0x0303, 0x0409, (uint8_t const *)&string3, sizeof(STR_SERIALNUMBER)},
};
