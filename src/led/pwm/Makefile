.PHONY: help

GREEN := $(shell tput -Txterm setaf 2)
YELLOW := $(shell tput -Txterm setaf 3)
RESET := $(shell tput -Txterm sgr0)
MCU=atmega32u2
CFLAGS=-Os -DF_CPU=16000000UL -mmcu=${MCU} -Wall -c

help: ## Show this help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "${YELLOW}%-16s${GREEN}%s${RESET}\n", $$1, $$2}' $(MAKEFILE_LIST)

clean: ## Remove compiled files.
	rm -f main.o wait.o pin.o main.hex main

build: ## Compile source code.
	avr-gcc ${CFLAGS} -o wait.o ../../../framework/wait.c
	avr-gcc ${CFLAGS} -o pin.o ../../../framework/pin.c
	avr-gcc ${CFLAGS} -I ../../../framework/ -o main.o main.c
	avr-gcc -mmcu=${MCU} wait.o pin.o main.o -o main
	avr-objcopy -O ihex -R .eeprom main main.hex

upload: ## Write firmware to microcontroller.
 	avrdude -F -V -c usbtiny -p ${MCU} -U flash:w:main.hex

download: ## Backup firmware from microcontroller.
	avrdude -V -c usbtiny -p ${MCU} -U flash:r:backup.hex:i

fuse: ## Write fuse to microcontroller.
	avrdude -c usbtiny -p ${MCU} -u -U lfuse:w:0xEF:m -U hfuse:w:0xD5:m

erase: ## Erase all on microcontroller.
	avrdude -c usbtiny -p ${MCU} -e -F

tty: ## Enter into TTY terminal.
	tio -b 57600 /dev/cu.usbserial-AD02CSHC
