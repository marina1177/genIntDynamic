#include "../includes/verle.h"

void io_write_input(char **av, t_params *params, t_arrv3	*arr){

	FILE *fp;

	if((fp = fopen(av[ARG_IO], "ab"))==NULL){
		io_error("Cant open input file\n");
		return;
	}
	//проверка что файл пустой
	fseek(fp,0,SEEK_END);
	long pos=ftell(fp);
	if(pos>0)
	{
		//это интегратор считал начальные условия и пишет каждый n-ый шаг
		// файл непустой.
		// начальные параметры уже есть в начале
		fclose(fp);
		io_error("Input file already exist and not empty!\n");
		//!TODO записывать arr в конец
		//!самая первая частица любого шага имеет отрицательное значение радиуса рахзмера(последнеее)
	}
	else{
	//это генератор пишет начальные условия и позиции

	// переходим в начал файла
		rewind(fp);

	// пишем общие параметры
		fwrite(params, sizeof(t_params), 1, fp);

	// пишем н.у. для каждой частицы
		printf("arr->len = %d\n", arr->len);
		for(int i =0; i < arr->size; i++){
			printf("write [%d]	x: %9f,		y: %9f,		z: %9f\n", i, arr->addr[i].x, arr->addr[i].y, arr->addr[i].z);
			fwrite(&(arr->addr[i]),sizeof(t_v3), 1, fp);
		}
	}
	fclose(fp);
	return;
}
