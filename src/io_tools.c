#include "../includes/verle.h"

void print_params(t_params *params){
	printf("amount_of_particles: %f\n", params->amount_of_particles);

	printf("tfull: %.20f\n", params->tfull);
	printf("tstep: %.20f\n", params->tstep);

	printf("freq: %f\n", params->freq);
	printf("U: %f\n", params->U);
	printf("Vdc: %f\n", params->V);

	printf("da: %f\n", params->da);
	printf("ra: %f\n", params->ra);


}

void print_state(t_v3 *v3, int indx, char order){

	if(order - 'd'==0){

		if(indx % 3 == 0 ){
			printf("[%d]	m: %.9f,	q: %.15f,	dp: %f\n", indx, v3->x, v3->y, v3->z);
		}
		else if(indx % 3 == 1){
			printf("[%d]	vx: %f,	vy: %f,	vz: %f\n", indx, v3->x, v3->y, v3->z);
		}
		else if(indx % 3 == 2){
			printf("[%d]	x: %f,	y: %f,	z: %f\n", indx, v3->x, v3->y, v3->z);
		}
	}

	if(order - 'a'==0){
		if(indx % 3 == 0 ){
		printf("[%d]	x: %f,	y: %f,	z: %f\n", indx, v3->x, v3->y, v3->z);
	}
		else if(indx % 3 == 1){
		printf("[%d]	vx: %f,	vy: %f,	vz: %f\n", indx, v3->x, v3->y, v3->z);
	}
		else if(indx % 3 == 2){
		printf("[%d]	m: %.9f,	q: %.15f,	dp: %f\n", indx, v3->x, v3->y, v3->z);
	}
	}
}

void read_params(FILE *fp, t_params *params){

	//t_params *params = malloc(sizeof(t_params));

	fread(&params->amount_of_particles, sizeof(params->amount_of_particles), 1, fp);

	fread(&params->tfull,				sizeof(params->tfull), 1, fp);
	fread(&params->tstep,				sizeof(params->tstep), 1, fp);

	fread(&params->freq,				sizeof(double), 1, fp);
	fread(&params->U,					sizeof(params->U), 1, fp);
	fread(&params->V,					sizeof(params->V), 1, fp);

	fread(&params->da,					sizeof(params->da), 1, fp);
	fread(&params->ra,					sizeof(params->ra), 1, fp);


	print_params(params);
	//free(params);
}

int read_state(FILE *fp, t_v3 *v3, int indx, char order){

	//t_v3 *v3 = malloc(sizeof(t_v3));

	int xs=-99;
	int ys =-99;
	int zs =-99;
	if((xs = fread(&v3->x,			sizeof(double), 1, fp)) >= 0 &&
		(ys = fread(&v3->y,			sizeof(double), 1, fp)) >= 0 &&
		(zs = fread(&v3->z,			sizeof(double), 1, fp)) >= 0){

		print_state(v3, indx, order);
		return 0;
	}

	printf("xs:%d; ys:%d; zs:%d;\n",xs, ys, zs);

	return -1;
	//free(v3);
}

void read_initial_states(FILE *fp){

	int indx = 0;
	for(int i = 0; i<AMOUNT_OF_PARTICLES*3; i++){
		indx = i % 3;
		if(indx==0){
			printf("INIT STATE PARTICLE #%d\n",i/3);
		}

		t_v3 v3 ;
		read_state(fp, &v3, indx, 'a');

		//printf("i")
	}

}
