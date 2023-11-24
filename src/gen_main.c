#include "../includes/verle.h"


int gen_main(){
	t_params *params;

	//1. создать структуру параметры
	params = (t_params *) malloc(1 * sizeof(t_params));

	//2. заплнить структуру параметры
	params->amount_of_particles = ;
	params->freq = ;
	params->tfull = ;
	params->tstep = ;
	params->U = ;
	params->nu = ;
	params->da = ;
	params->ra = ;
	params->V = ;

	//3. создать структуру начальных услвий всех частиц s_array_v3
	//4. заплнить начальные условия координаты с учетом радиуса частиц
	//5. io_write_input - запись параметрв и начальных услвий в файл
	//6. закрыть файл
}
