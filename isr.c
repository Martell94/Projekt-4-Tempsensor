#include "header.h"

static volatile uint32_t timer0_counter = 0;
static volatile uint16_t timer1_counter = 0;

/********************************************************************************
								PCINT0_vect: 
Tryckknappens interruptrutin. Kontaktstudsar beivras genom att st�nga av interrupts
p� tryckknappen, och sedan k�ra en kort cykel p� Timer 1.

Eftersom man vill ha f�r�ndring p� stigande flank anv�nder man ocks� en if-sats,
s� att uppdatering av temperaturinformation sker f�rst n�r knappen inte l�ngre 
�r nedtryckt. Sedan kallar man p� get_temp funktionen och nollst�ller timer 0,
s� att den p� nytt b�rjar r�kna upp till 60s.
********************************************************************************/
ISR (PCINT0_vect){
	
	PCMSK0 &= ~(1 << PCINT3); //St�nger av interrupts p� knappen.
	TIMSK1 |= (1 << OCIE1A); //Initierar timer 1.
		
	if (!BUTTON_PRESSED){
		get_temp(&tmp36);
		timer0_counter = 0; //Nollst�ller timer 0.
	}
}

/********************************************************************************
								TIMER0_OVF_vect;
		Overflow-timer med interrupt en g�ng i minuten, varvid den 
		printar temperaturen i den seriella monitorn.
********************************************************************************/
ISR (TIMER0_OVF_vect){
	
	if (++timer0_counter >= TIMER0_MAXV){
		get_temp(&tmp36); 
		timer0_counter = 0;
	}
	return;
}

/********************************************************************************
								TIMER1_COMPA_vect;
		Compare-timer som ser avbrott var 25:e ms. Anv�nds som debounce.
********************************************************************************/
ISR (TIMER1_COMPA_vect){
	
	if(++timer1_counter >= TIMER1_MAXV){
		
		timer1_counter = 0; //Nollst�ller timer-r�knaren.
		
		PCICR = (1 << PCIE0); //Sl�r �terigen p� interrupts p� knappen.
		PCMSK0 |= (1 << PCINT3);
	}
	
	return;
}

