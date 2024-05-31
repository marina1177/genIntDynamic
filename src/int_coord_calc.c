
#include "../includes/verle.h"

void full_step_coord_calc(t_arrv3 *arr, double dt){
		// X=X+V*dt;
	printf("\nfull_step_coordinates:\n");
	for(int n = 0; n < arr->len; n++){
		arr->addr[n*3].x = arr->addr[n*3].x + arr->addr[n*3+1].x*dt;
		arr->addr[n*3].y = arr->addr[n*3].y + arr->addr[n*3+1].y*dt;

		printf("[%d][%d]: x:%.10f; y:%.10f\n", n,n*3 ,arr->addr[n*3].x,arr->addr[n*3].y);

		if(THREE_DIM == 1){
			arr->addr[n*3].z = arr->addr[n*3].z + arr->addr[n*3+1].z*dt;
		}
	}
}
