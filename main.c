/********************************************************************************
								main.c: 
			Programmets huvudfil. H�r deklarerar vi globala
			variabler och kallar p� v�r headerfil.
********************************************************************************/
#include "header.h"

temp_t tmp36; //deklareras f�r bruk i hela filen.

/********************************************************************************
								(int)main: 
		Programmets startpunkt. Hoppar omdelbart till setup-rutinen.
						
		(RETURN 0); f�r att indikera att programmets exekvering g�tt v�l. 
			
********************************************************************************/
int main(void){
	
	setup();
	
	while (1){
		
	}
	
	return 0;
}

