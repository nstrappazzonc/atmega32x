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

build: ## Compile source code.
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o main.o main.c
	avr-gcc -mmcu=atmega328p main.o -o main
	avr-objcopy -O ihex -R .eeprom main main.hex

upload: ## Write firmware to microcontroller.
	avrdude -c usbtiny -p ATMEGA32u4 -U flash:w:main.hex
