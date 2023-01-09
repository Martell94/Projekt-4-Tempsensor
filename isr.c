#include "header.h"

static volatile uint32_t timer0_counter = 0;
static volatile uint16_t timer1_counter = 0;

/********************************************************************************
								PCINT0_vect: 
Tryckknappens interruptrutin. Kontaktstudsar beivras genom att stänga av interrupts
på tryckknappen, och sedan köra en kort cykel på Timer 1.

Eftersom man vill ha förändring på stigande flank använder man också en if-sats,
så att uppdatering av temperaturinformation sker först när knappen inte längre 
är nedtryckt. Sedan kallar man på get_temp funktionen och nollställer timer 0,
så att den på nytt börjar räkna upp till 60s.
********************************************************************************/
ISR (PCINT0_vect){
	
	PCMSK0 &= ~(1 << PCINT3); //Stänger av interrupts på knappen.
	TIMSK1 |= (1 << OCIE1A); //Initierar timer 1.
		
	if (!BUTTON_PRESSED){
		get_temp(&tmp36);
		timer0_counter = 0; //Nollställer timer 0.
	}
}

/********************************************************************************
								TIMER0_OVF_vect;
		Overflow-timer med interrupt en gång i minuten, varvid den 
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
		Compare-timer som ser avbrott var 25:e ms. Används som debounce.
********************************************************************************/
ISR (TIMER1_COMPA_vect){
	
	if(++timer1_counter >= TIMER1_MAXV){
		
		timer1_counter = 0; //Nollställer timer-räknaren.
		
		PCICR = (1 << PCIE0); //Slår återigen på interrupts på knappen.
		PCMSK0 |= (1 << PCINT3);
	}
	
	return;
}

