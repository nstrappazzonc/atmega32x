FROM alpine
RUN apk --no-cache add bash ncurses make gcc-avr avr-libc avrdude
WORKDIR /workdir
