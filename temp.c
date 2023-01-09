#include "header.h"

/********************************************************************************
							(void)init_temps:
		Anv�nds f�r att initiera v�r tempsensor, samt adc p� sensorn.
				
				temp_t* self: V�r struktinstans.
				uint8_t pin: Den pin som sensorn l�ses av p�.
********************************************************************************/

void init_temps(temp_t* self, const uint8_t pin){
	
	self->pin = pin;
	init_adc(self);
	
	return;
}

/********************************************************************************
								(void)get_temp:
	H�r m�ter vi faktiskt de v�rden vi f�r ut ifr�n sensorn. F�r att f�r j�mnare
	m�tdata har jag valt att ta tre olika m�tningar, med 100ms mellanrum mellan
	varje m�tning. Detta skrivs sedan till struktinstansen och skickas vidare 
	till print_temp.
	
						temp_t* self: V�r struktinstans.
********************************************************************************/
void get_temp(temp_t* self){
	
	double t1,t2,t3;
	
	double input_voltage = adc_getv(self) /1023.0 * 5.0;
	t1 = (input_voltage * 100) - 50;
	delay_ms(100);
	
	input_voltage = adc_getv(self) /1023.0 * 5.0;
	t2 = (input_voltage * 100) - 50;
	delay_ms(100);
	
	input_voltage = adc_getv(self) /1023.0 * 5.0;
	t3 = (input_voltage * 100) - 50;
	
	self->temp = ((t1 + t2 + t3)/3);
	
	print_temp(self);
	
	return;
}


/********************************************************************************
							(void)print_temp:
		Denna funktion skriver informationen fr�n get_temp till den seriella 
		monitorn.
						
					temp_t* self: V�r struktinstans.
********************************************************************************/

void print_temp(temp_t* self){
		
	
	serial_print_string("Current room temperature is: ");
	serial_print_double(self->temp);
	serial_print_string("C \r");
	
	return;
}

