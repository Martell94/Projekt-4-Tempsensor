#include "header.h"

/********************************************************************************
							(void)init_temps:
		Används för att initiera vår tempsensor, samt adc på sensorn.
				
				temp_t* self: Vår struktinstans.
				uint8_t pin: Den pin som sensorn läses av på.
********************************************************************************/

void init_temps(temp_t* self, const uint8_t pin){
	
	self->pin = pin;
	init_adc(self);
	
	return;
}

/********************************************************************************
								(void)get_temp:
	Här mäter vi faktiskt de värden vi får ut ifrån sensorn. För att får jämnare
	mätdata har jag valt att ta tre olika mätningar, med 100ms mellanrum mellan
	varje mätning. Detta skrivs sedan till struktinstansen och skickas vidare 
	till print_temp.
	
						temp_t* self: Vår struktinstans.
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
		Denna funktion skriver informationen från get_temp till den seriella 
		monitorn.
						
					temp_t* self: Vår struktinstans.
********************************************************************************/

void print_temp(temp_t* self){
		
	
	serial_print_string("Current room temperature is: ");
	serial_print_double(self->temp);
	serial_print_string("C \r");
	
	return;
}

