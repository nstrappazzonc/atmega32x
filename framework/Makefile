GREEN   := $(shell tput -Txterm setaf 2)
YELLOW  := $(shell tput -Txterm setaf 3)
RESET   := $(shell tput -Txterm sgr0)
MCU=atmega32u2
CC=avr-gcc
OBJCOPY=avr-objcopy
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=${MCU} -Wall -I ../../../framework/

.PHONY: help

help: ## Show this help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "${YELLOW}%-16s${GREEN}%s${RESET}\n", $$1, $$2}' $(MAKEFILE_LIST)

clean: ## Remove compiled files.
	rm -f *.o *.hex main

build: ## Compile source code.
	${CC} $(CFLAGS) -c -o main.o main.c
	${CC} -mmcu=${MCU} -I ../../../framework/ main.o -o main
	${OBJCOPY} -O ihex -R .eeprom main main.hex

upload: ## Write firmware to microcontroller.
	avrdude -F -V -c usbtiny -p ${MCU} -U flash:w:main.hex

download: ## Backup firmware from microcontroller.
	avrdude -V -c usbtiny -p ${MCU} -U flash:r:backup.hex:i

fuse: ## Write fuse to microcontroller.
	avrdude -c usbtiny -p ${MCU} -u -U lfuse:w:0xEF:m -U hfuse:w:0xD5:m

tty: ## Enter into TTY terminal.
	tio -b 57600 /dev/cu.usbserial-AD02CSHC
