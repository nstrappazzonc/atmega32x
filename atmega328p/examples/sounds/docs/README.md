# Sonidos

Hagamos un repaso breve de términos,

- El **[sonido](https://es.wikipedia.org/wiki/Sonido)** es cualquier fenomeno que involucra una propagación de ondas mecanicas a travez de un medio fluido con una frecuencia dentro un rango audible.
- La **[melodía](https://es.wikipedia.org/wiki/Melodía)** es una sucesión de sonidos que es percibida como una sola entidad. Se desenvuelve en una secuencia lineal, es decir, a lo largo del tiempo, y tiene una identidad y significado propio dentro de un entorno sonoro particular.

Ahora que sabemos la diferencia de ambos términos, continuemos.

Es posible introducir sonidos o melodias de 8-bit a 8000 Hz usando el canal mono dentro del MCU, se reproduce usando el PWM o un DAC del MCU y estará conectado a la salida con un Zumbador Piezoeléctrico (Piezo Buzzer).

Las melodias de 8-bit, en el mundo binario se expresa matematicamente cómo 2^8 donde su valor esta entre 0 y 255, cada uno de estos 256 valores equivalen a un tono, y en combinación se pueden hacer melodias.

```
2^8 = (2^4)^2
2^8 = (16)^2 => 16 × 16 = 256
```

El MCU de genera varias formas de ondas; seno, triangular y cuadrada. Cada una hace un efecto de sonido particular. En [este video](https://www.youtube.com/watch?v=qV10Gb-Dvao) te lo explican.

Considere que no todas las melodias se escucharán bien bajo esta configuración, deben estar hechos para 8-bit y no es suficiente con exportarlos, solo algunos ya adaptados o creados para esta configuración.

Existen dos formas de incluir melodias, desconosco el nombre correcto de cada una, entonces me invento lo que veen aquí:

## Simple

Se logra con un arreglo donde estan solo las notas, suelen usar esta forma para efectos de sonido y ocupa mas espacio.

Para incorporar sonidos debemos hacer solo tres pasos:

1. Convertir cualquier archivo de sonido al formato [.wav](https://en.wikipedia.org/wiki/WAV) con las siguientes propiedades: 8-bit, 8000 Hz y señal mono. Haga uso de [éste tutorial](https://github.com/nstrappazzonc/atmega32x/blob/main/atmega328p/examples/sounds/docs/mp3_to_wav.md) para lograrlo.
2. Convertir el archivo .wav a un arreglo de valores para C usando la herramienta [wav2c](https://github.com/nstrappazzonc/atmega32x/tree/main/atmega328p/examples/sounds/wav2c).
3. [Reproducir el arreglo usando el PWM](https://github.com/nstrappazzonc/atmega32x/blob/main/atmega328p/examples/sounds/main.c) con la frecuencia adecuada. aqui hay un pwm de dos escalas 256 y 16k explicarlo mejor...

## Complejo

Se logra con dos arreglos y una tabla de notas, la tabla de notas no varia según la melodía, de los arreglos uno se usa para las notas y otro para la duración de cada nota. Este formato hace que sea más cercano al deseado dentro de las posibilidades y ocupa muy poco espacio en el MCU. Este tipo de melodias se pueden obtener haciendo una conversion de un formato abierto llamado MusicXML donde se guardan las partituras.

Es muy importante considerar que el MCU tiene una capacidad limitada de memoria y solo se podrá introducir una cierta cantidad de sonidos o melodias, aplicando ciertos trucos podrá combinar y repetir segmentos de sonidos para producir melodias más complejas, incluso apoyandote con otros componentes electronicos. Todo esto depende de lo que queremos conseguir, esto quiere decir que hay un límite en la definición, el tamaño del arreglo y depende directamente del tiempo del sonido o melodia.

Dentro de este directorio tiene todo lo que hace falta para lograrlo.
