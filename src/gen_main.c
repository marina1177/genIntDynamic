#include "../includes/verle.h"

int gen_main(char **av){
	t_params *params;
	t_arrv3	*arr;

	//1. создать структуру параметры
	params = (t_params *) malloc(1 * sizeof(t_params));
	printf("sizeof of t_params: %ld\n", sizeof(t_params));

	//2. заплнить структуру параметры
	set_default_params(params);
	printf("finished: set_default_params\n");
	print_params(params);

	//3. создать структуру начальных услвий всех частиц s_array_v3
	arr = arrv3_malloc(AMOUNT_OF_PARTICLES);
	
	//4. заплнить начальные условия координаты с учетом радиуса частиц
	set_initial_values(arr);
	printf("finished: set_initial_values\n");

	//prepare data  x y z | vx vy vz |m q r|
	//если последнеее поле 3ей структуры (радиус) для 1ой частицы
	// - отрицательное, то это начало тайм степа
	arr->addr[2].z *= -1;

	//5. io_write_input - запись параметрв и начальных услвий в файл
	io_write_input(av, params, arr);
	printf("finished: io_write_input\n");

	free(params);
	arrv3_free(arr);

	return 0;
}
