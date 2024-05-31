#include "../includes/verle.h"

double	 calc_particle_mass(double particle_diameter){
	double rp = particle_diameter/2;

	double mass = (4*PARTICLE_RHO*3.1416*pow(rp, 3)) / 3;

	return mass;
}

int		check_intersections(double *coords, int i){

//	Find the centre and radius of each sphere.
	double xc = coords[i];
	double yc = coords[i+1];
	double zc = coords[i+2];
	//printf("check\n[%d]: x: %f, y: %f, z: %f\n", i, xc,yc,zc);
	double xc_distance;
	double yc_distance;
	double zc_distance;
	// Find the magnitude of the distance of the line between the sphere's centres
	double magnitude = PARTICLE_DIAMETER;

	int cnt = 0;
	while(cnt < i/3){
		//printf("cnt=%d, p#=%d\n", cnt, i/3);
		if(cnt==i){
			continue;
		}
		xc_distance = fabs(coords[cnt*3] - xc) ;
		//printf("[%d] xc_dist=%f\n",cnt*3, xc_distance);
		yc_distance = fabs(coords[cnt*3+1] - yc);
		//printf("[%d] yc_dist=%f\n", cnt*3+1, yc_distance);
		zc_distance = fabs(coords[cnt*3+2] - zc);
		//printf("[%d] zc_dist=%f\n",cnt*3+2, zc_distance);

		//if (magnitude distance of the line) ≤ radius they do intersect.
		if(xc_distance <= magnitude || yc_distance <=magnitude || zc_distance <=magnitude){
			printf("Intersection with particle #%d \n", cnt+1);
			return 1;
		}
		cnt++;
	}
	//If (magnitude distance of line) > radius they do not intersect,
	//printf("No any intersection\n");
	return 0;
}

double	randfrom(double min, double max)
{
    double range = (max - min);
    double div = RAND_MAX / range;
    return min + (rand() / div);
}

void	set_coords(double *coords, int i){
	int iter = 0;
	do{
		coords[i] = randfrom(-TRAP_ELECTRODE_DIAMETER-TRAP_ELECTRODE_DISTANCE/2, +TRAP_ELECTRODE_DIAMETER+TRAP_ELECTRODE_DISTANCE/2);
		coords[i+1] = randfrom(-TRAP_ELECTRODE_DIAMETER-TRAP_ELECTRODE_DISTANCE/2, +TRAP_ELECTRODE_DIAMETER+TRAP_ELECTRODE_DISTANCE/2);
		coords[i+2] = randfrom(-TRAP_ELECTRODE_DIAMETER-TRAP_ELECTRODE_DISTANCE/2, +TRAP_ELECTRODE_DIAMETER+TRAP_ELECTRODE_DISTANCE/2);

		//printf("[%d] x: %f, y: %f, z: %f\n", i/3, coords[i],coords[i+1],coords[i+2]);

		iter++;

	}while (check_intersections(coords, i));
}

void	set_velocity(t_v3 *vlct){

	vlct->x = randfrom(-0.03, 0.03);//[m/s]
	vlct->y = randfrom(-0.03, 0.03);
	vlct->z = 0;
}


void	set_initial_values(t_arrv3 *arr){

	printf("Start: set_initial_values\n");
	double *coords;

	//x y z & dp(check intersections)
	coords = (double*)malloc(AMOUNT_OF_PARTICLES*4*sizeof(double));

	arr->size = AMOUNT_OF_PARTICLES*3;
	arr->len = AMOUNT_OF_PARTICLES;
	int i = 0;
	while(i < AMOUNT_OF_PARTICLES*3){
	//random coordinates [0;0] for the first particle
		if(i == 0){
			//printf("particle #%d\n", 0);
			coords[0]=0;coords[1]=0;
			//! для 3х мерного случая - середина длины
			coords[2]=0;
		}else {
			//printf("particle #%d\n", i/3);
			set_coords(coords, i);

			arr->addr[i].x = coords[i];
			arr->addr[i].y = coords[i+1];
			arr->addr[i].z = coords[i+2];
		}
		printf("[%d]	x: %f,	y: %f,	z: %f\n", i/3, coords[i],coords[i+1],coords[i+2]);

	//| vx vy vz |
		set_velocity(&(arr->addr[i+1]));
		printf("[%d]	vx: %f,	vy: %f,	vz: %f\n", i/3, arr->addr[i+1].x, arr->addr[i+1].y, arr->addr[i+1].z);

	//|m q dp|
		double q_div_m = Q_DIV_M_PARAM*Q_EL/((4*PARTICLE_RHO*M_PI*pow(10*10e-6,3))/3);

		if(VARIABLE_DIAMETER == 0){
			arr->addr[i+2].z = PARTICLE_DIAMETER/pow(10,6);
			printf("PARTICLE DIAMETER: %d [mkm]\n",  PARTICLE_DIAMETER);
			double rp = arr->addr[i+2].z / 2;
			arr->addr[i+2].x = calc_particle_mass(arr->addr[i+2].z);

			// q = m*(q/m)
			arr->addr[i+2].y = Q_DIV_M_PARAM*Q_EL;
		}else{
			printf("VARIABLE_DIAMETER != 0\n");
			//dp
			arr->addr[i+2].z = randfrom(PARTICLE_DIAMETER_MIN, PARTICLE_DIAMETER_MAX);
			//m
			arr->addr[i+2].x = calc_particle_mass(arr->addr[i+2].z);
			//q
			double q_div_m = Q_DIV_M_PARAM*Q_EL/((4/3)*PARTICLE_RHO*M_PI*pow(10*10e-6,3));
			arr->addr[i+2].y = arr->addr[i+2].x*q_div_m;
		}
		printf("[%d]	m: %.15f,	q: %.20f,	d: %f\n", i/3, arr->addr[i+2].x, arr->addr[i+2].y, arr->addr[i+2].z);

		i+=3;
	}

	free(coords);
	return;
}
