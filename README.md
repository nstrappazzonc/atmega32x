# ATMega32u2 Examples

All examples inside in this repository are configure to use 16 MHz.

## Requirements

To program AVRs, you will need the free avr-gcc compiler, avr-libc, AVRDUDE, and other associated tools.

### Mac OS X

To install this tools, we recommend first installing [Homebrew](https://brew.sh). Then run the following commands to install AVRDUDE and homebrew-avr:

```bash
xcode-select --install
brew install avrdude
brew tap osx-cross/avr
brew install avr-gcc
brew install dfu-programmer
```
