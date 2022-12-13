/* Header file with all the essential definitions for a given type of MCU */
#include "MK60D10.h"

/* Constants specifying delay loop duration */
#define tdelay1 32768
#define tdelay2 10

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
	SIM->SCGC5 = SIM_SCGC5_PORTB_MASK;

	/* Set corresponding PTB pins (connected to LED's) for GPIO functionality */
	PORTB->PCR[5] = ( PORT_PCR_MUX(0x01) ); // D9
	PORTB->PCR[4] = ( PORT_PCR_MUX(0x01) ); // D10
	PORTB->PCR[3] = ( PORT_PCR_MUX(0x01) ); // D11
	PORTB->PCR[2] = ( PORT_PCR_MUX(0x01) ); // D12

	/* Change corresponding PTB port pins as outputs */
	PTB->PDDR = GPIO_PDDR_PDD( 0x3C );
	PTB->PDOR |= GPIO_PDOR_PDO( 0x3C);

	for (;;) {
		counter++;

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
    }
    /* Never leave main */
    return 0;
}
