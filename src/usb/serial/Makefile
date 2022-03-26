.PHONY: help

GREEN := $(shell tput -Txterm setaf 2)
YELLOW := $(shell tput -Txterm setaf 3)
RESET := $(shell tput -Txterm sgr0)
MCU=atmega32u2
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=${MCU} -Wall -c

help: ## Show this help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "${YELLOW}%-16s${GREEN}%s${RESET}\n", $$1, $$2}' $(MAKEFILE_LIST)

clean: ## Remove compiled files.
	rm *.o
	rm *.hex
	rm main

check: ## Verify communication to microcontroller.
	avrdude -c avrisp -b57600 -p ATMEGA328P -P /dev/cu.usbserial-AD02CSHC

build: ## Compile source code.
	avr-gcc ${CFLAGS} -c -o main.o main.c
	avr-gcc ${CFLAGS} -c -o usb.o usb.c
	avr-gcc -mmcu=${MCU} usb.o main.o -o main
	avr-objcopy -O ihex -R .eeprom main main.hex

upload: ## Write firmware to microcontroller.
	avrdude -F -V -c usbtiny -p ${MCU} -U flash:w:main.hex
