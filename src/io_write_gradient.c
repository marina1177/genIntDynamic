#include "../includes/verle.h"

void io_write_gradient_to_file(double *extremes,double Ex[g_n_pot][g_n_pot], double Ey[g_n_pot][g_n_pot]){

	FILE *fp;
	char nl = '\n';

	if((fp = fopen(GRAD_FILE, "w"))==NULL){
		io_error("Cant open input file\n");
		return;
	}
	printf("file: %s\n", GRAD_FILE);
	double n_pot = extremes[6];
	double h_pot = extremes[7];

	fprintf(fp, "%.3g\n",n_pot);
	for(int i = 0; i < n_pot; i++){
		for(int j = 0; j < n_pot; j++){
			 fprintf(fp, "%.20f\t",Ex[i][j]);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "%.3g\n",n_pot);
	for(int i = 0; i < n_pot; i++){
		for(int j = 0; j < n_pot; j++){
			 fprintf(fp, "%.20f\t",Ey[i][j]);
		}
		fprintf(fp, "\n");
	}

	fclose(fp);
	exit(0);
}
