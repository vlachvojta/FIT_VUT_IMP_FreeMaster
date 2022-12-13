/* This is originally from Ing. JOSEF STRNADEL Ph.D. (V|B)UT FIT. But it was tweaked and simplified to behave as follows:
 * Set LEDs (9-12) as output. When button SW6 is pressed, all LEDs (9-12) flips their current value.
 * author: strnadel@fit.vut.cz
 * co-author: xvlach22@fit.vutbr.cz, 2022
 */

/* Header file with all the essential definitions for a given type of MCU */
#include "MK60D10.h"
#include "core_cm4.h"
#include "mcg.h"

/*
 * Port E ISR
 */
void PORTE_IRQHandler() {
	// Clear all Port E interrupt flag
	PORTE->ISFR = PORT_ISFR_ISF_MASK;

	// Toggle all LEDs
	PTB->PTOR = (0b111100);
}

int main(void) {
	unsigned int x = 0, y = 0; // Counter variables

	// Configure the MCG to run in BLPE mode. (50 MHz)
	MCG_FEI_BLPE();

	// Enable clocks on Port B
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK;

	/* Configure the Signal Multiplexer for the LEDs (GPCLR is a method to set multiple pins simultaneously)
	 *                   D12 - D9
	 */
	PORTB->GPCLR = ( ((0b111100)) << 16) | PORT_PCR_MUX(0x01);

	/* Set corresponding PTB port pins as outputs */
	PTB->PDDR = (0b111100);
	PTB->PSOR = (0b111100);

	// Configure the Signal Multiplexer for SW6, configure SW6 to interrupt on falling edge
	PORTE->PCR[11] = PORT_PCR_MUX(0x01) | PORT_PCR_IRQC(0b1010); // SW6

	// Clear the Interrupt flags in Port E
	PORTE->ISFR = 0xFFFFFFFF;

	// Clear the Interrupt pending flag in the NVIC just in case
	NVIC->ICPR[2] = (1 << 27);

	// Enable the Interrupt in the NVIC
	NVIC->ISER[2] = (1 << 27);

	for(;;) {
		// Do nothing.
	}

	return 0;
}
