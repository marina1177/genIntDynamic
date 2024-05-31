#ifndef PARAMS_H

# define THREE_DIM					0
# define TWO_DIM					1

# define SIN_S						1
# define SQUARE_S					0

# define AMOUNT_OF_PARTICLES		1
# define TRAP_FREQ					50 //[Hz]
# define FULL_TIME					50//[periods] params->tfull =  FULL_TIME50;
# define TIME_STEP		 			300 // 1/params->freq/TIME_STEP
# define TRAP_U_ALTERNATIVE			5000 //[V]
# define TRAP_U_DIRECT			    0//[V]
# define NU_AIR			            18.27*pow(10,-6)
# define TRAP_ELECTRODE_DIAMETER    0.004 //[m]
# define TRAP_ELECTRODE_DISTANCE    0.019 // [m]

# define VARIABLE_DIAMETER			0  // 0-если монодисперсные частицы размера PARTICLE_DIAMETER
// с отношением заряда к массе  PARTICLE_Q зарядов электрона е

# define Q_EL						-1.6e-19
# define Q_DIV_M_PARAM				150000
# define PARTICLE_DIAMETER_MAX		10*10e-4 //[m]
# define PARTICLE_DIAMETER_MIN		2*10e-5 //[m]
# define PARTICLE_DIAMETER			10 //[mkm]
# define PARTICLE_RHO				3990 //[]

# define MAP_FILE				"potential_ahalf.txt"
# define GRAD_FILE				"grad_ahalf.txt"
# define WRITE_GRAD				0
// >> ./verle -i test_31_05.bin potential_ahalf.txt

#endif

