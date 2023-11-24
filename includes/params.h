#ifndef PARAMS_H

# define AMOUNT_OF_PARTICLES		5
# define TRAP_FREQ					50 //[Hz]
# define FULL_TIME					10*1/TRAP_FREQ
# define TIME_STEP		 			1/TRAP_FREQ/100
# define TRAP_U_ALTERNATIVE			5000 //[V]
# define TRAP_U_DIRECT			    0//[V]
# define NU_AIR			            18.27*pow(10,-6)
# define TRAP_ELECTRODE_DIAMETER    0.004
# define TRAP_ELECTRODE_DISTANCE    0.019

# define PARTICLE_DIAMETER          2*10e-5 //[m]	
# define PARTICLE_RHO                3.95e3 //[]
# define PARTICLE_Q                  98000//??[e]
# define PARTICLE_M                  PARTICLE_RHO *(4/3)*pow(PARTICLE_DIAMETER/2, 3);

// particle->rho = 3.95e3;
// 	particle->d = 2*10e-5;
// 	particle->m = particle->rho*(4/3)*M_PI *pow(particle->d/2, 3);
// 	particle->q = 5e-16;
#endif

