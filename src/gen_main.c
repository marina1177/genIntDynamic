#include "../includes/verle.h"

int check_intersections(double *coords, int i){

//	Find the centre and radius of each sphere.
	double xc = coords[i*3];
	double yc = coords[i*3+1];
	double zc = coords[i*3]+2;

// Find the magnitude of the distance of the line between the sphere's centres 
	double magnitude = PARTICLE_DIAMETER;
//If (magnitude distance of line) > radius they do not intersect, 
//if (magnitude distance of the line) ≤ radius they do intersect.


}

double randfrom(double min, double max) 
{
    double range = (max - min); 
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

int gen_main(){
	t_params *params;
	t_arrv3	*arr;

	//1. создать структуру параметры
	params = (t_params *) malloc(1 * sizeof(t_params));

	//2. заплнить структуру параметры
	params->amount_of_particles = AMOUNT_OF_PARTICLES;
	params->freq = TRAP_FREQ;
	params->tfull = FULL_TIME;
	params->tstep = TIME_STEP;
	params->U = TRAP_U_ALTERNATIVE;
	params->nu = NU_AIR;
	params->da = TRAP_ELECTRODE_DIAMETER;
	params->ra = TRAP_ELECTRODE_DISTANCE;
	params->V = TRAP_U_DIRECT;

	//3. создать структуру начальных услвий всех частиц s_array_v3
	arr = (t_arrv3 *) malloc(1 * sizeof(t_arrv3));
	//					x y z | vx vy vz |m q r|
	arr->addr = (t_v3 *) malloc(AMOUNT_OF_PARTICLES*3 * sizeof(t_v3));
	arr->len = AMOUNT_OF_PARTICLES;
	arr->size = AMOUNT_OF_PARTICLES;

	//4. заплнить начальные условия координаты с учетом радиуса частиц
	
	double coords[AMOUNT_OF_PARTICLES*3];
	int i = 0;
	while(i < arr->len){
		//random for the first particle
		if(i == 0){
			
		}
		i+=3;
	}
	//5. io_write_input - запись параметрв и начальных услвий в файл
	//6. закрыть файл
}
