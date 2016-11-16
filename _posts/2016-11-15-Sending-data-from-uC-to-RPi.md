---
layout: post
title: ATMega328P hello world on Linux Mint
---

Sending data from uC to Raspberry Pi using serial UART interface

## Serial interface

UART - Universal Asynchronous Receiver/Transmitter is a hardware device for for asynchronous serial communication. Asynchronous means that both end points are not synchronized by common clock source. Transmission speed (baud rate) is predefined and both endpoint should use the same. **This is reason why you shouldn't use internal uC oscilator, which is very imprecise (it deviation is up to to 10%).** Instead external crystal oscilator should be used which uncertainity is only 0.1%.

![UART](https://upload.wikimedia.org/wikipedia/commons/thumb/2/24/UART_timing_diagram.svg/1600px-UART_timing_diagram.svg.png)

## Atmega 328p

Controller expose serial interface on interfaces RXD/TXD
![](http://www.hobbytronics.co.uk/image/data/tutorial/arduino-hardcore/atmega328-arduino-pinout.jpg)

## Raspbery Pi 
