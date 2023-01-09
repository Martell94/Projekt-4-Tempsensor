/********************************************************************************
								main.c: 
			Programmets huvudfil. Här deklarerar vi globala
			variabler och kallar på vår headerfil.
********************************************************************************/
#include "header.h"

temp_t tmp36; //deklareras för bruk i hela filen.

/********************************************************************************
								(int)main: 
		Programmets startpunkt. Hoppar omdelbart till setup-rutinen.
						
		(RETURN 0); för att indikera att programmets exekvering gått väl. 
			
********************************************************************************/
int main(void){
	
	setup();
	
	while (1){
		
	}
	
	return 0;
}

