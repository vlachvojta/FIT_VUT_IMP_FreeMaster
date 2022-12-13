#include "MK60D10.h"
#include "core_cm4.h"


uint32_t dwt_ctrl = 0; /* bit mask for DWT->CTRL */

#define MEASUREMENT_MAX_SAMPLES 10
struct measurement {
	uint32_t cycles;
	uint32_t sleep_cycles;
	uint32_t exception_cycles;

	uint32_t lsu_cycles;
	uint32_t fold_counter;
	uint32_t cpi_cycles;
};

struct measurements {
	struct measurement measurement[MEASUREMENT_MAX_SAMPLES];
	struct measurement avg;
	int position;
};

void measurement_store_result_and_increment(struct measurements *measurements)
{
	measurements->measurement[measurements->position].cycles = DWT->CYCCNT;
	measurements->measurement[measurements->position].sleep_cycles = DWT->SLEEPCNT;
	measurements->measurement[measurements->position].exception_cycles = DWT->EXCCNT;

	measurements->measurement[measurements->position].lsu_cycles = DWT->LSUCNT;
	measurements->measurement[measurements->position].fold_counter = DWT->FOLDCNT;
	measurements->measurement[measurements->position].cpi_cycles = DWT->CPICNT;


	measurements->position++;
}

void compute_statistics(struct measurements *measurements)
{
	for (int position = 0; position < MEASUREMENT_MAX_SAMPLES; position++) {
		measurements->avg.cycles +=measurements->measurement[position].cycles;
		measurements->avg.sleep_cycles +=measurements->measurement[position].sleep_cycles;
		measurements->avg.exception_cycles +=measurements->measurement[position].exception_cycles;

		measurements->avg.lsu_cycles +=measurements->measurement[position].lsu_cycles;
		measurements->avg.fold_counter +=measurements->measurement[position].fold_counter;
		measurements->avg.cpi_cycles +=measurements->measurement[position].cpi_cycles;
	}

	measurements->avg.cycles /= MEASUREMENT_MAX_SAMPLES;
	measurements->avg.sleep_cycles /= MEASUREMENT_MAX_SAMPLES;
	measurements->avg.exception_cycles /= MEASUREMENT_MAX_SAMPLES;

	measurements->avg.lsu_cycles /= MEASUREMENT_MAX_SAMPLES;
	measurements->avg.fold_counter /= MEASUREMENT_MAX_SAMPLES;
	measurements->avg.cpi_cycles /= MEASUREMENT_MAX_SAMPLES;

}

/* structures with results of all conducted measurements */
struct measurements measurement_1 = { 0 };
struct measurements measurement_2 = { 0 };
struct measurements measurement_3 = { 0 };

/*
 * Set dwt registers to 0, prepare bit mask for control register
 */
void init_dwt()
{
	CoreDebug->DEMCR |= DWT_CTRL_EXCTRCENA_Msk;  /* enable DWT hardware */

	DWT->CTRL		= 0;	/* reset control register */
	DWT->CYCCNT		= 0;	/* reset cpu cycle counter register */
	DWT->EXCCNT		= 0;	/* reset exception cycle counter register */
	DWT->SLEEPCNT 	= 0;  	/* reset sleep cycle counter register */

	DWT->LSUCNT 	= 0;	/* reset load store counter register */
	DWT->FOLDCNT	= 0; 	/* reset instruction fold counter register */
	DWT->CPICNT		= 0;  	/* reset cpi counter register */

	dwt_ctrl |= DWT_CTRL_CYCCNTENA_Msk;
	dwt_ctrl |= DWT_CTRL_SLEEPEVTENA_Msk;
	dwt_ctrl |= DWT_CTRL_EXCEVTENA_Msk;

	dwt_ctrl |= DWT_CTRL_LSUEVTENA_Msk;
	dwt_ctrl |= DWT_CTRL_FOLDEVTENA_Msk;
	dwt_ctrl |= DWT_CTRL_CPIEVTENA_Msk;
}

#define start_dwt() DWT->CTRL |= dwt_ctrl

#define stop_dwt() DWT->CTRL &= ~dwt_ctrl


int main(void)
{

//	Example code, uncomment by ctrl + /

//	sampleX:
//	init_dwt();
//	start_dwt();
//		// YOUR CODE HERE
//	stop_dwt();
//
//	measurement_store_result_and_increment(&measurement_X);
//	if (measurement_X.position != MEASUREMENT_MAX_SAMPLES)
//		goto sampleX;


	sample1:
	init_dwt();
	start_dwt();
		int x = 0;
		int c = 3;
		double b = 5;
		for (int i =0; i < 200; i++) {
			x = c + b;
			c = 2 / 3;
			sample1_label:
			x = c + c;
			if (x > 2)
				goto sample1_label;
			else
				x = 3;
		}
	stop_dwt();

	measurement_store_result_and_increment(&measurement_1);

	if (measurement_1.position != MEASUREMENT_MAX_SAMPLES)
		goto sample1;
	compute_statistics(&measurement_1);

	sample3:
		init_dwt();
		start_dwt();
			int xa = 0;
		stop_dwt();

		measurement_store_result_and_increment(&measurement_3);

		if (measurement_3.position != MEASUREMENT_MAX_SAMPLES)
			goto sample3;
		compute_statistics(&measurement_3);



	loop:
		goto loop;
    return 0;
}
