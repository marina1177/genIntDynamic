#include "../includes/verle.h"

void set_default_params(t_params * params){

	params->amount_of_particles = AMOUNT_OF_PARTICLES;

	double freq = (double)TRAP_FREQ;
	params->freq = freq;

	double periods = FULL_TIME;
	params->tfull = periods/50;
	params->tstep = 1/params->freq/TIME_STEP;

	params->U = TRAP_U_ALTERNATIVE;
	params->V = TRAP_U_DIRECT;

	params->da = TRAP_ELECTRODE_DIAMETER;
	params->ra = TRAP_ELECTRODE_DISTANCE;

}
