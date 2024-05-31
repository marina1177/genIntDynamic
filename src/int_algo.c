#include "../includes/verle.h"

void int_algo(char **av,t_params *params, t_arrv3 *arr, double *extremes, double Ex[g_n_pot][g_n_pot], double Ey[g_n_pot][g_n_pot] ){
	FILE * fp;

	if((fp = fopen(av[ARG_IO], "ab"))==NULL){
		io_error("Cant open output file\n");
		return;
	}

	int		N = 0 ;
	int		exclude[AMOUNT_OF_PARTICLES];
	//на 100 шагов по 3 структуры для каждой частицы
	t_v3 	buffer[300 * AMOUNT_OF_PARTICLES];
	t_v3	acc[AMOUNT_OF_PARTICLES];

	//Forces
	t_v3 fSt[AMOUNT_OF_PARTICLES];
	t_v3 fC[AMOUNT_OF_PARTICLES];
	t_v3 f_tr[AMOUNT_OF_PARTICLES];

	//НУ
	memset(acc,0,sizeof(acc));
	for(int i=0; i<AMOUNT_OF_PARTICLES; i++){
		exclude[i]=1;
	}


	N = params->tfull / params->tstep;
	// цикл времени
	int step_cnt = 0 ;
	double t = 0;
	double dt = params->tstep;
	printf("amount of steps:%d\nt_step:%.10f\n", N, dt);

	for(int i = 0; i < N; i++){
		printf("\nSTEP #%d time: %f\n", i, t);
		// velocity half-step
		 // !TODO: Qmatrix=(Q.*P').*(Q.*P')';
		//V=(V+0.5*A*dt).*P;
		half_step_velocity_calc(acc, arr, dt, exclude);

		//Координата на полном шаге X=X+V*dt;
		full_step_coord_calc(arr, dt);

		t=t+dt;
		exception(exclude,arr);

	// forces calculation
		//Stokes
		stokes(arr, fSt);

		//interparticle_forces Colomb
		interparticle_forces(arr, fC);

		//tension_for_particle(X(:,1),X(:,2))
		tension_for_particle(params, exclude,arr, extremes, Ex, Ey,t, f_tr);

		//accelertion calc
		acceleration_calc(acc, arr, fSt, fC, f_tr);

		//Скорость на полном шаге
		//V=(V+0.5*A*dt).*P;
		full_step_velocity_calc(acc, arr, dt, exclude);


		if(i % 10 == 0){
		//запись в буффер
			io_write_to_buffer(buffer, arr, step_cnt);
			step_cnt++;
		}


		if(step_cnt == 100){
		//запись в конец output файла
			printf("io_write_to_outfile %d steps from buffer\n", step_cnt);
			io_write_to_outfile(fp, buffer, step_cnt*arr->size);
			step_cnt = 0;
			memset(buffer,0,sizeof(buffer));
		}

		if(sum(exclude, arr->len) == 0){
			break;
		}
	}

	//записать в файл
	printf("io_write_to_outfile %d steps from buffer\n", step_cnt);

	io_write_to_outfile(fp, buffer, step_cnt*arr->size);
	fclose(fp);
}
