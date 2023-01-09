#include "header.h"

static inline void init_interrupts();
static inline void init_timer();

/********************************************************************************
								(void)setup: 
			K�rs en g�ng. Initierar interrupts, timer, tempsensor,
			seriell �verf�ring och AD-omvandling.
********************************************************************************/
void setup(){
	
	read(PORTB, BUTTON);
	init_interrupts();
	init_timer();
	serial_init(9600);
	init_temps(&tmp36, SENSOR);
	init_adc(&tmp36);
	
	asm("SEI");
	return;
}

/********************************************************************************
							(void)init_interrupts: 
	Lever upp till sitt namn. Initierar PCI-interrupts p� v�r knapp s� att 
	temperaturen sedan skrivs till v�r seriella monitor n�r knappen tryckts ned.
********************************************************************************/
static inline void init_interrupts(){
	
	PCICR |= (1<<PCIE0);
	PCMSK0 |= (1<<BUTTON);
	
	return;
}

/********************************************************************************
							(void)init_timer: 
	Initierar timer 0, som anv�nds f�r att printa temperaturen en g�ng i minuten,
	samt timer 1, som anv�nds f�r att debouncea knapptryckningar.
********************************************************************************/
static inline void init_timer(){
	
	TCCR0B = (1 << CS01);
	TIMSK0 = (1 << TOIE0);
	
	TCCR1B = (1 << CS11) | (1 << WGM12); 
	OCR1A = 256; 
	TIMSK1 = (1 << OCIE1A);
	
	return;
}

