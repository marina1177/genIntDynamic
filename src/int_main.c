#include "../includes/verle.h"

int				int_main(char **av){
	t_params	*params;
	t_arrv3		*arr;
	t_map		*map;

	//1. создать структуру параметры
	params = (t_params *) malloc(1 * sizeof(t_params));

	//2. создать структуру с указателем на массив всех частиц s_array_v3
	if((arr = (t_arrv3 *) malloc(1 * sizeof(t_arrv3))) == NULL){
		io_error("[Generator:t_arrv3 *arr] allocate error!\n");
	}

	//3. прочитать файл , выделить память в массиве,
	// записать в масив начальные условия
	// (либо начальные условия либо последний шаг, на котором оборвалась запись)
	// количество частиц может отличаться от константы!
	io_read_input(av, params, arr);

	// printf("\nCHECK\n");
	// for(int i =0; i<arr->size; i++){
	// 	print_state(&(arr->addr[i]), i, 'a');
	// }

	//! TODO перенести в генератор и только считывать и сохранять в структуру файл с градиентом
	//4. считать и сохранить сетку напряжения
	// двумерный массив s_v3
	// x y z | Ex Ey Ez
	int map_size = 0;
	map_size = io_read_map(av, &map);
	// gradient
	// Xmin | Ymin | Zmin | Xmax | Ymax| Zmax | n_pot | h_pot
	double extremes[8] = {0};
	//extremes:
	//Xmin | Ymin | Zmin | Xmax | Ymax | Zmax | n_pot | h_pot
	get_extremes(map, map_size,extremes);

	int n_pot = extremes[6];

	double Ex[n_pot][n_pot];
	double Ey[n_pot][n_pot];

	tension(map, extremes, Ex, Ey);

	// printf("minX:%.4f	minY:%.4f\n",(extremes)[0], (extremes)[1]);
	// printf("maxX:%.4f	maxY:%.4f\n", (extremes)[3], (extremes)[4]);

// с началом каждого шага - менять указатели
	// prev очищается memset(0) и curr -> становится prev
	//каждый 10 шаг записывается в буфер на 100 шагов,
	// и по заполнению записывается в файл
	//5.
	int_algo(av,params, arr, extremes,  Ex, Ey);

	return 0;

}
