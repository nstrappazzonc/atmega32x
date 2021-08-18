.PHONY: help

GREEN := $(shell tput -Txterm setaf 2)
YELLOW := $(shell tput -Txterm setaf 3)
RESET := $(shell tput -Txterm sgr0)

help: ## Show this help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "${YELLOW}%-16s${GREEN}%s${RESET}\n", $$1, $$2}' $(MAKEFILE_LIST)

clean: ## Remove compiled files.
	rm main.o
	rm main.hex
	rm main

check: ## Verify communication to microcontroller.
	avrdude -c avrisp -b57600 -p ATMEGA328P -P /dev/cu.usbserial-AD02CSHC

build: ## Compile source code.
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o l74hc165/l74hc165.o l74hc165/l74hc165.c
	avr-gcc -mmcu=atmega328p main.o l74hc165/l74hc165.o -o main
	avr-objcopy -O ihex -R .eeprom main main.hex

upload: ## Write firmware to microcontroller.
	avrdude -F -V -c avrisp -b57600 -p ATMEGA328P -P /dev/cu.usbserial-AD02CSHC -U flash:w:main.hex

download: ## Backup firmware from microcontroller.
	avrdude -F -V -c avrisp -b57600 -p ATMEGA328P -P /dev/cu.usbserial-AD02CSHC -U flash:r:backup.hex:i

tty: ## Enter into TTY terminal.
	tio -b 57600 /dev/cu.usbserial-AD02CSHC
