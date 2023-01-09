/********************************************************************************
									timer.h
		Inneh�ller div. makrodefinitioner f�r att underl�tta anv�ndning av timer.
********************************************************************************/
#ifndef TIMER_H_
#define TIMER_H_

#include "header.h"

#define TIMER0_ELAPSED_MS 60000 // Timer 0 l�per ut efter en minut.
#define TIMER0_MAXV (uint32_t)(TIMER0_ELAPSED_MS / 0.128 + 0.5) // H�r definierar vi maxv�rdet f�r Timer0.

#define TIMER1_ELAPSED_MS 30 // Timer 1 l�per ut efter 30ms.
#define TIMER1_MAXV (uint16_t)(TIMER1_ELAPSED_MS / 0.128 + 0.5) // H�r definierar vi maxv�rdet f�r Timer1.

#endif /* TIMER_H_ */