#include "../includes/verle.h"

void io_error(char *error_msg){
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void io_read_input(void **av, t_params *params,t_arrv3 *crds, t_arrv3 *vlcts, t_arrv3 *props){

	FILE *fp;

	if(fp = fopen(av[ARG_IO], "rb")==NULL){
		io_error("Cant open input file\n");
		return;
	}

	fread(params, sizeof(params),1, fp);
	fseek (fp,0,SEEK_END);
	//учитывается fread последнего поля field
	int fpos = ftell(fp)-sizeof(double);

	double field;
	int count = 0;

	while(1){
		fread(&field, sizeof(field), 1, fp);
		printf("field(r) = %f\n", field);
		count++;
		if(field < 0)
			break;
		fpos -= sizeof(t_v3)*3;
		//int fseek(FILE *fp, long число_байт, int начало);
		fseek (fp,fpos,SEEK_CUR);
	}
}

