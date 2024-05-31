#include "../includes/verle.h"

void tension_for_particle(t_params *params, int *exclude, t_arrv3 *arr, double *extremes,
        double Ex[g_n_pot][g_n_pot], double Ey[g_n_pot][g_n_pot], double t, t_v3 *f_tr){
    //extremes:
	//Xmin | Ymin | Zmin | Xmax | Ymax | Zmax | n_pot | h_pot
	double Xmin = extremes[0];
	double Ymin = extremes[1];
	double h_pot = extremes[7];

	double omega = 2*M_PI*params->freq;
	int i = 0, j = 0;

	printf("tension_for_particle\n");

	for(int k = 0; k < arr->len; k++){
		i = 0;
		j = 0;
		if(exclude[k] == 0){
			continue;
		}
		printf("[%d]: x:%.20f; y:%.20f\n", k, arr->addr[k*3].x,arr->addr[k*3].y);
		while(Ymin + i*h_pot < arr->addr[k*3].y){
			i++;
		}
		while(Xmin + j*h_pot < arr->addr[k*3].x){
			j++;
		}
		printf("k:%d; i:%d; j:%d\n", k, i, j);
		if(SIN_S == 1){
			// E(k,1:2)=-Q(k)*[Ex(i,j) Ey(i,j)]*U*square(omega*t);
			//!TODO: добавить знак заряда в параметры # define
			f_tr[k].x = arr->addr[k*3+2].y*Ex[i][j]*params->U*sin(omega*t);
			f_tr[k].y =  arr->addr[k*3+2].y*Ey[i][j]*params->U*sin(omega*t);
			printf("trap force[%d]: fx:%f; fy:%f; fz:%f\n", k, f_tr[k].x, f_tr[k].y, f_tr[k].z);

			//! TODO для 3 измерений
			//f_tr[k].z =
		}else if(SQUARE_S == 1){
				printf("! TODO:add square wave form\n");
		}
	}
}
