#include "header.h"

void init_adc (temp_t* self){
	
	(void)adc_getv(self);
	return;
}

uint16_t adc_getv(temp_t*self){
	
	ADMUX = (1<<REFS0) | self->pin;
	ADCSRA = (1<<ADEN) | (1<<ADSC) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
	while (read(ADCSRA, ADIF) == 0);
	set (ADCSRA, ADIF);
	
	return ADC;
}
