/* Header file with all the essential definitions for a given type of MCU */
#include "MK60D10.h"
#include "mcg.h"
#include "io.h"
#include "uart.h"

int main(void) {

	// Transition back to FEI mode (default mode upon restart)
	MCG_FEI_BLPE();

	// Configure the TX and RX pins for UART5
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK;
	PORTE->PCR[8] = PORT_PCR_MUX(0x03);
	PORTE->PCR[9] = PORT_PCR_MUX(0x03);

	// Initialize the UART.
	// Use TERM_PORT = UART3_BASE_PTR for the 9pin serial port. (Defined in uart.h)
	// Configure for 50 MHz peripheral clock and 115200 target baud rate.
	uart_init(TERM_PORT, 50000, 115200);

	for(;;) {

		// uart_putchar(TERM_PORT, 'A');
		// Wait until a key is pressed
		while(char_present() == 0);
		// out_char (in_char());

		// Print to the terminal which key was pressed.
		 printf("You pressed '%c'\n\r", in_char());
	}

	return 0;
}
