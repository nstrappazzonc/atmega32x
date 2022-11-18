# ATMega32u2 Examples

All examples inside in this repository are configure to use 16 MHz.

Examples:

- LED: Normal blink, Fade (PWM) and RGB.
- Push buttom.
- USB communications device class (or USB CDC class) is a Serial communication.

## Requirements

To program AVRs, you will need the free avr-gcc compiler, avr-libc, AVRDUDE, and other associated tools.

### Linux

```bash
sudo apt-get install -y gcc-avr binutils-avr avr-libc gdb-avr avrdude libusb-dev dfu-programmer
```

### Mac OS X

To install this tools, we recommend first installing [Homebrew](https://brew.sh). Then run the following commands to install AVRDUDE and homebrew-avr:

```bash
xcode-select --install
brew install avrdude
brew tap osx-cross/avr
brew install avr-gcc
brew install dfu-programmer
```
