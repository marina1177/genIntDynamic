#include "../includes/verle.h"

static void interparticle_dist(t_arrv3 *arr, double Rdist[AMOUNT_OF_PARTICLES][AMOUNT_OF_PARTICLES] ){

	for(int i = 0; i<arr->len; i++){
		for( int j =0; j < arr->len; j++){

			if(i == j){
				Rdist[i][j] = -1;
				//printf(" | %.3f",Rdist[i][j]);
				continue;
			}
			Rdist[i][j] = sqrt(pow((arr->addr[i*3].x - arr->addr[j*3].x),2) + pow((arr->addr[i*3].y - arr->addr[j*3].y),2)+ pow((arr->addr[i*3].z - arr->addr[j*3].z),2));
			//printf(" | %.3f",Rdist[i][j]);
		}
		//printf("  [%d]\n",i);
	}
}

static void calc_projection(t_arrv3 *arr, t_v3	projection[AMOUNT_OF_PARTICLES][AMOUNT_OF_PARTICLES]){
	//printf("projection\n");
	for(int i = 0; i<arr->len; i++){
		for( int j =0; j < arr->len; j++){

			if(i == j){
				projection[i][j].x = 0;
				projection[i][j].y = 0;
				projection[i][j].z = 0;
				continue;
			}
			projection[i][j].x = arr->addr[i*3].x * arr->addr[j*3].x;
			projection[i][j].y = arr->addr[i*3].y * arr->addr[j*3].y;
			projection[i][j].z = arr->addr[i*3].z * arr->addr[j*3].z;
		}
	}
}

static void calc_Colomb_const(t_arrv3 *arr, double	Rdist[AMOUNT_OF_PARTICLES][AMOUNT_OF_PARTICLES], double constant[AMOUNT_OF_PARTICLES][AMOUNT_OF_PARTICLES] ){

	for(int i = 0; i<arr->len; i++){
		for( int j =0; j < arr->len; j++){

			if(i == j){
				constant[i][j] = 0;
				continue;
			}
			//constanta=(K*Qmatrix./R.^3);
			constant[i][j] = K_CONST*(arr->addr[i*3+2].y*arr->addr[j*3+2].y) / pow(Rdist[i][j],3);
		}
	}
}

static void calc_Colomb_force(t_arrv3 *arr,  t_v3	projection[AMOUNT_OF_PARTICLES][AMOUNT_OF_PARTICLES],
			double constant[AMOUNT_OF_PARTICLES][AMOUNT_OF_PARTICLES],  t_v3 *fC){

	printf("\nColomb\n");

	for(int i = 0; i<arr->len; i++){
		for( int j =0; j < arr->len; j++){

			if(j == 0){
				fC[i].x = constant[i][j]*projection[i][j].x;
				fC[i].y = constant[i][j]*projection[i][j].y;
				fC[i].z = constant[i][j]*projection[i][j].z;
				continue;
			}
	// f1(:,1)=constanta.*X1*ones(n,1);
    // f1(:,2)=constanta.*X2*ones(n,1);
    // f1(:,3)=constanta.*X3*ones(n,1);

			fC[i].x += constant[i][j]*projection[i][j].x;
			fC[i].y += constant[i][j]*projection[i][j].y;
			fC[i].z += constant[i][j]*projection[i][j].z;
		}
		printf("Colomb force[%d]: fx:%f; fy:%f; fz:%f\n", i, fC[i].x, fC[i].y, fC[i].z);

	}

}

void interparticle_forces(t_arrv3 *arr, t_v3 *fC){

	double	prt_rad = 0;
	double	Rdist[AMOUNT_OF_PARTICLES][AMOUNT_OF_PARTICLES];
	t_v3	projection[AMOUNT_OF_PARTICLES][AMOUNT_OF_PARTICLES];
	double	constant[AMOUNT_OF_PARTICLES][AMOUNT_OF_PARTICLES];

	interparticle_dist(arr, Rdist);
	// ???
	calc_projection(arr, projection);

	calc_Colomb_const(arr, Rdist, constant);
	calc_Colomb_force(arr, projection, constant, fC);
}

