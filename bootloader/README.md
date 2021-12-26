# Bootloader for ATmega32U2

It is a [megaAVR DFU USB Bootloaders](https://ww1.microchip.com/downloads/aemDocuments/documents/OTH/ProductDocuments/SoftwareLibraries/Firmware/megaUSB_DFU_Bootloaders.zip) for [ATmega32U2](https://www.microchip.com/en-us/product/ATmega32u2)

## Fuses
- EXT  = 0xF4
- HIGH = 0xD9
- LOW  = 0x5E

```
avrdude -c usbtiny -p atmega32u2 -u -F -U lfuse:w:0x5E:m -U hfuse:w:0xD9:m -U efuse:w:0xF4:m
```
