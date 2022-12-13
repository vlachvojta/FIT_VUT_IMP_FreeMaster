/* Header file with all the essential definitions for a given type of MCU */
#include "MK60D10.h"

/* Constants specifying delay loop duration */
#define	tdelay1	32768
#define tdelay2	10

/* Auxiliary global variable */
int counter = 0;

/* Variable delay loop */
void delay(int t1, int t2)
{
	int i, j;

	for(i=0; i<t1; i++) {
		for(j=0; j<t2; j++);
	}
}

int main(void)
{
	/* Turn on all port clocks */
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK;

	/* Set corresponding PTB pins (connected to LED's) for GPIO functionality */
	PORTB->PCR[5] = ( PORT_PCR_MUX(0x01) ); // D9
	PORTB->PCR[4] = ( PORT_PCR_MUX(0x01) ); // D10
	PORTB->PCR[3] = ( PORT_PCR_MUX(0x01) ); // D11
	PORTB->PCR[2] = ( PORT_PCR_MUX(0x01) ); // D12

	PORTE->PCR[10] = PORT_PCR_MUX(0x01); // SW2
	PORTE->PCR[12] = PORT_PCR_MUX(0x01); // SW3
	PORTE->PCR[27] = PORT_PCR_MUX(0x01); // SW4
	PORTE->PCR[26] = PORT_PCR_MUX(0x01); // SW5
	PORTE->PCR[11] = PORT_PCR_MUX(0x01); // SW6

	/* Change corresponding PTB port pins as outputs */
	PTB->PDDR = GPIO_PDDR_PDD( 0x3C );
	PTB->PDOR |= GPIO_PDOR_PDO( 0x3C);

	//Turn all the LEDs sequentialy ON!
    PTB->PDOR &= ~(1 << 5);
    delay(tdelay1, tdelay2);
    PTB->PDOR &= ~(1 << 4);
    delay(tdelay1, tdelay2);
    PTB->PDOR &= ~(1 << 3);
    delay(tdelay1, tdelay2);
    PTB->PDOR &= ~(1 << 2);
    delay(tdelay1, tdelay2);

    //Turn all the LEDs sequentialy OFF!
   	PTB->PDOR |= (1 << 2);
   	delay(tdelay1, tdelay2);
   	PTB->PDOR |= (1 << 3);
   	delay(tdelay1, tdelay2);
   	PTB->PDOR |= (1 << 4);
   	delay(tdelay1, tdelay2);
   	PTB->PDOR |= (1 << 5);
   	delay(tdelay1, tdelay2);

	for (;;) {
		counter++;

		/* Evaluation of SW2 state */
		if ( (PTE->PDIR & (1 << 10)) != 0 ) {
			PTB->PDOR |= (1 << 5);
		} else {
		    PTB->PDOR &= ~(1 << 5);
		}

		/* Evaluation of SW3 state */
		if ( (PTE->PDIR & (1 << 12)) != 0 ) {
		    PTB->PDOR |= (1 << 4);
		} else {
		  	PTB->PDOR &= ~(1 << 4);
		}

		/* Evaluation of SW4 state */
		if ( (PTE->PDIR & (1 << 27)) != 0 ) {
		    PTB->PDOR |= (1 << 3);
		} else {
		    PTB->PDOR &= ~(1 << 3);
		}

		/* Evaluation of SW5 state */
		if ( (PTE->PDIR & (1 << 26)) != 0 ) {
		    PTB->PDOR |= (1 << 2);
	    } else {
	        PTB->PDOR &= ~(1 << 2);
	    }

		/* Evaluation of SW6 state */
		if ( (PTE->PDIR & (1 << 11)) != 0 ) {
	        PTB->PDOR |= GPIO_PDOR_PDO( 0x3C );
	    } else {
	        PTB->PDOR &= ~GPIO_PDOR_PDO( 0x3C );
	    }
    }
    /* Never leave main */
    return 0;
}
