#include "../includes/verle.h"

void io_write_input(void **av, t_params *params,t_arrv3 *crds, t_arrv3 *vlcts, t_arrv3 *props){

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
		// файл непустой.
		io_error("Input file already exist and not empty!\n");
	}
	//переходим в начал файла
	rewind(fp);
	


}
