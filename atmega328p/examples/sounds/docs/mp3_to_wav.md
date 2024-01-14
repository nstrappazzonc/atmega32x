# Convertir .mp3 y otros formatos a .wav

The format of .wav files containing PCM data (a stream of sample amplitudes) is reasonably well documented. You can find the information on the web.

https://en.wikipedia.org/wiki/Pulse-code_modulation

Para el desarrollo de este ejemplo, usaremos el archivo [MacStartUp.mp3](https://github.com/nstrappazzonc/atmega32x/blob/main/atmega328p/examples/sounds/waves/MacStartUp.mp3) para convertirlo a [MacStartUp.wav](https://github.com/nstrappazzonc/atmega32x/blob/main/atmega328p/examples/sounds/waves/MacStartUp.wav), y por último lo convertiremos a un arreglo de C [MacStartUp.h](https://github.com/nstrappazzonc/atmega32x/blob/main/atmega328p/examples/sounds/waves/MacStartUp.h).

1. Habra el archivo [MacStartUp.mp3](https://github.com/nstrappazzonc/atmega32x/blob/main/atmega328p/examples/sounds/waves/MacStartUp.mp3) con [Audacity](https://www.audacityteam.org).
2. Exporte el audio con el siguiente formato cómo se muestra en la siguiente imagen; Format=wav, Channels=mono, Sample Rate=8000 Hz, Encoding=Unsigned 8-bit PCM.

![](https://github.com/nstrappazzonc/atmega32x/blob/main/atmega328p/examples/sounds/docs/audacity.png?raw=true)

3. Convierta el archivo de audio [MacStartUp.wav](https://github.com/nstrappazzonc/atmega32x/blob/main/atmega328p/examples/sounds/waves/MacStartUp.wav) a un arreglo en C usando la herramienta y escribiendo el comando:

```bash
./wav2c ../waves/MacStartUp.wav ../waves/MacStartUp.h MacStartUp
```

Ahora puedes incluir el arreglo en [main.c](https://github.com/nstrappazzonc/atmega32x/blob/main/atmega328p/examples/sounds/main.c) para reproducirlo.
