---
layout: post
title: ATMega328P hello world on Linux Mint
---

Next you can update your site name, avatar and other options using the _config.yml file in the root of your repository (shown below).

![_config.yml]({{ site.baseurl }}/images/config.png)

The easiest way to make your first post is to edit this one. Go into /_posts/ and update the Hello World markdown file. For more instructions head over to the [Jekyll Now repository](https://github.com/barryclark/jekyll-now) on GitHub.

In this post I will describe how to setup Linux Mint desktop to be able to put some basic `hello world` style code sample.

## Setting up environment

Required hardware:

- ATMega328P uController
- USB-ASP ready programator
- resisors, capaticors, LED
- 5V power supply
- prototype board

First of all you need to install all required tools.

#### avrdude
[source](http://savannah.nongnu.org/projects/avrdude)

[project info](http://www.nongnu.org/avrdude/user-manual/avrdude_toc.html#SEC_Contents)

avrdude is an application that is used to put your code already transformed to hex string into chip EEPROM.

#### libs and other tools

Following tools should be installed:

```
sudo apt-gat install -y \
libelf1 libelf-dev \
libusb-1.0-0 libusb-1.0-0-dev \
libftdi1 libftdi1-dev \
libftdi-dev autoconf \
bison flex bc libtool
```


## Hello world uC app

#### create sample C code
```
# prog.c

#include <avr/io.h> //Defines pins, ports, etc.
#include <util/delay.h>

int main(void) {

  DDRB |= (1 << PB0); //Data Direction Register B: writing a 1 to the bit enables output

  while (1) {
    PORTB= 0b00000001; //turns on LED attached to port PB0
    _delay_ms(100); //creates a 1-second delay
    PORTB= 0b00000000; //Turns off all B pins, including PB0
    _delay_ms(100); //creates another 1-second delay
  }

  return (0); //this line is never actually reached
}
```

#### compile source using avr-gcc
`avr-gcc -mmcu=atmega328p prog.c -o prog`

#### Translate compiled code to hex format
`avr-objcopy -O ihex prog prog.hex`

#### put this hex formatted file into uC EEPROM
`sudo avrdude -c usbasp -p m328p -B 5 -U flash:w:prog.hex -v`

According to [this](http://electronics.stackexchange.com/a/181900) answer on stackexchage, new AVR chips come configured to use the chip's internal oscillator as a clock source, with the CLOCKDIV8 ("divide clock frequency by 8") fuse set. This means that they run at 1MHz. The maximum programming frequency the chip supports is clock speed / 4, i.e. 250kHz. The USBASP defaults to 375kHz, which is too fast, so you need to slow it down.

You do this either by setting the "slow SCK" jumper of your USBASP, if it has one, or by using the avrdude `-B` option

![](/content/images/2016/11/Untitled-Diagram.png)


**Useful links:**

- http://uczymy.edu.pl/wp/blog/2015/09/05/oznaczenia-kondensatorow-ceramicznych/
- http://serwis-tv.com/opornik.html
- http://elektroniczny.eu/jak-dobrac-rezystor-do-diody-led/
- http://lesion.github.io/
- http://www.learningaboutelectronics.com/Articles/Program-AVR-chip-using-a-USBASP-with-10-pin-cable.php Connecting programmer to uC
- https://majsterkowo.pl/programowanie-mikrokontrolerow-za-pomoca-programatora-usbasp/
- http://www.learningaboutelectronics.com/Articles/Atmega328-pinout.php ATMEGA382 pinout
- http://www.learningaboutelectronics.com/Articles/AVR-blinking-LED-circuit.php Cone example from this article
- http://www.fischl.de/usbasp/ USP-ASP programmer page. Shuld not be needed, when you have bought programer with already installed firmware
- http://www.robotyka.net.pl/linux-i-avr-cz-1/
- https://gcc.gnu.org/onlinedocs/gcc/AVR-Options.html gnu-gcc avr options


**TODO:**

- prepare docker image with preinstalled tools
