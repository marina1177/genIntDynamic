#include "../includes/verle.h"

t_params *params_malloc(){
	t_params *params;

	if((params = (t_params *) malloc(1 * sizeof(t_params))) == NULL){
		io_error("[Generator: t_params *params] allocate error!\n");
	}
	return params;
}

t_arrv3 *arrv3_malloc(int amount_of_particles){
	t_arrv3 *arr;

	//3. создать структуру начальных услвий всех частиц s_array_v3
	if((arr = (t_arrv3 *) malloc(1 * sizeof(t_arrv3))) == NULL){
		io_error("[Generator:t_arrv3 *arr] allocate error!\n");
	}
	//					x y z | vx vy vz |m q dp|
	if((arr->addr = (t_v3 *) malloc(amount_of_particles*3 * sizeof(t_v3)))==NULL){
		io_error("[Generator: t_v3 *addr] allocate error!\n");
	}

	arr->len = amount_of_particles;
	arr->size = amount_of_particles*3;

	return arr;
}

void arrv3_free(t_arrv3 *arr){

	free(arr->addr);
	free(arr);
}
