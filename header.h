#ifndef HEADER_H_
#define HEADER_H_

#include "misc.h"
#include "temp.h"
#include "adc.h"
#include "serial.h"
#include "timer.h"

extern temp_t tmp36; //Ser till att sensorn är synlig i hela filen.

#define set(reg,bit) reg |= (1<<bit)
#define clr(reg,bit) reg &= ~(1<<bit)
#define read(reg,bit) (reg & (1<<bit))

#define BUTTON PORTB3
#define BUTTON_PRESSED read(PINB, BUTTON)

#define SENSOR PORTC2
#define SENSORVAL read(PINC, SENSOR)

void setup();

#endif /* HEADER_H_ */