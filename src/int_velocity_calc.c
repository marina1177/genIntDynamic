#include "../includes/verle.h"

//сохраняю в
void half_step_velocity_calc(t_v3 *acc, t_arrv3 *arr, double dt, int	*exclude){
	//V=(V+0.5*A*dt).*P;
	printf("half_step_velocity:\n");
	for(int n = 0; n < arr->len; n++){
		printf("before [%d][%d]: vx:%.20f; vy:%.20f\n", n,n*3+1,arr->addr[n*3+1].x,arr->addr[n*3+1].y);

		arr->addr[n*3+1].x = (arr->addr[n*3+1].x + 0.5 * acc[n].x*dt)*exclude[n];
		arr->addr[n*3+1].y = (arr->addr[n*3+1].y + 0.5* acc[n].y*dt)*exclude[n];

		printf("[%d][%d]: vx:%.20f; vy:%.20f\n", n,n*3+1,arr->addr[n*3+1].x,arr->addr[n*3+1].y);
		if(THREE_DIM == 1){
			arr->addr[n*3+1].z = (arr->addr[n*3+1].z+0.5*acc[n].z*dt)*exclude[n];
		}
	}
}

void full_step_velocity_calc(t_v3 *acc, t_arrv3 *arr, double dt, int *exclude){

	//V=(V+0.5*A*dt).*P;
	printf("full_step_velocity:\n");
	for(int n = 0; n< arr->len; n++){
		printf("before [%d][%d]: vx:%.20f; vy:%.20f\n", n,n*3+1,arr->addr[n*3+1].x,arr->addr[n*3+1].y);

		arr->addr[n*3+1].x = (arr->addr[n*3+1].x + 0.5*acc[n].x*dt)*exclude[n];
		arr->addr[n*3+1].y = (arr->addr[n*3+1].y + 0.5*acc[n].y*dt)*exclude[n];

		printf("after [%d][%d]: vx:%.20f; vy:%.20f\n", n,n*3+1,arr->addr[n*3+1].x,arr->addr[n*3+1].y);

		if(THREE_DIM == 1){
			arr->addr[n*3+1].z = (arr->addr[n*3+1].z + 0.5*acc[n].z*dt)*exclude[n];
		}
	}
}
