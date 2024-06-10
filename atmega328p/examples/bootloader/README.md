# ATmega328p Bootloader Tutorial

Un **bootloaders** y en este caso para algunos microcontroladores AVR como el ATmega328p emtre otros, es esencialmente un programa básico que se ejecuta dentro del MCU y está almacenado en una memoria no volátil. En pocas palabras, es el primer programa que se ejecuta al iniciar. Se utilizan para facilitar la conexión y el uso entre un PC y el MCU reduciendo la cantidad de hardware adicional por software, este puede entender varios protocolos de comunicación cómo el Serial.

Desde un caso [simple]() y didáctico, para ir entendiendo cómo funciona, se puede utilizar un bootloaders para que escriba el binario de un programa y lo ejecute cada vez que se inicie el MCU. Desde un punto de vista más habitual y [complejo](), se utiliza, por ejemplo, para leer información del MCU al PC o viceversa, usando el protocolo de comunicación Serial y poder leer o escribir el binario de un programa y ejecutarlo, cómo el poder definir algunas opciones de configuración en el proceso de inicio.

## Configurar los fusibles del MCU

El bootloaders puede ser de un determinado tamaño y depende de la complejidad de su codigo, por ejemplo; Mientras más protocolos de comunicaciones use, más lógica habra y más ocupa. Si solo usas un protocolo, este ocupará menos.

Conocer el tamaño que ocupa el bootloaders nos permite hacer dos cosas; Calcular la dirección de inicio del programa, y la cantidad de memoria que se necesita ser almacenado. El inicio del bootloaders se realiza luego de la instrucción RESET. La configuración se realiza ajustando los fusibles BOOTRST, BOOTSZ1 y BOOTSZ0.



## Recursos externos

- [optiboot](https://github.com/Optiboot/optiboot).
- [AVR Bootloader – Tutorial #18](https://www.electroschematics.com/avr-bootloader)
https://learn.adafruit.com/arduino-tips-tricks-and-techniques/bootloader
https://www.pocketmagic.net/simple-avr-bootloader-tutorial/

https://github.com/pavelrevak/avrprog/blob/master/avrboot/avrboot.c
https://github.com/vankxr/avr-bl/blob/master/main.cpp
https://github.com/m3y54m/simple-avr-bootloader
https://github.com/rbarreiros/AVR109_SPI_Bootloader

https://github.com/madtoyslab/AVR_ATmega328P


https://github.com/Trel725/chavrprog
https://github.com/rrevans/ubaboot

https://www.avrfreaks.net/s/topic/a5C3l000000UlgaEAC/t193411
https://www.avrfreaks.net/s/topic/a5C3l000000BrfjEAC/t392637


https://github.com/jacobsa/go-serial
https://github.com/npat-efault/picocom
