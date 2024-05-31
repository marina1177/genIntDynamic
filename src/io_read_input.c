#include "../includes/verle.h"

void io_error(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

void load_last_step(FILE *fd, int fpos, t_v3** addr){

	t_v3 *ptr;

	t_v3 v3;
	int offset = 0;


	printf("fpos:%d\n", fpos);

	fseek(fd, 0, SEEK_END); // Going to end of file
	int fpos_end = ftell(fd) - sizeof(t_v3);
	printf("fpos end:%d\n", fpos_end);

	int count = 1;
		while(offset <= fpos_end ){

			printf("[%d] fpos:%d;	offset:%d\n", count, fpos, offset);

			if (read_state(fd, &v3, count, 'a') == -1)
			{
				handle_error("input file read error!\n");
			}

			//offset = count * sizeof(v3);
			fseek(fd, offset, fpos);
			// ptr[i].x = v3.x;
			// ptr[i].y = v3.y;
			// ptr[i].z = v3.z;

			count++;
		}



		// ptr[i].x = v3.x;
		// ptr[i].y = v3.y;
		// ptr[i].z = v3.z;

		// ptr = (*addr);
		// fread(&(ptr[i].x),			sizeof(t_v3), 1, fd);
		// fread(&(ptr[i].y),			sizeof(t_v3), 1, fd);
		// fread(&(ptr[i].z),			sizeof(t_v3), 1, fd);

		//print_state(&(ptr[i]), indx, 'a');


}

int set_fd_to_last_step(FILE *fd, t_arrv3 *arr){
	int fp_start;
	int fpos_end;
	int count;
	int N ;
	int offset;
	t_v3 v3;
	t_v3 *ptr;

	// FILE *fd = *fd_adr;
	fp_start = ftell(fd);
	printf("fp_start after params: %d\n", fp_start);

	// чтение снизу вверх
	fseek(fd, 0, SEEK_END); // Going to end of file

	// учитывается fread последнего поля field
	fpos_end = ftell(fd) - sizeof(t_v3);

	printf("fp end of file: %ld\n", ftell(fd));
	printf("fp last v3: %d\n", fpos_end);

	count = 1;
	N = fpos_end - fp_start;
	offset = 0;
	while (-offset <= N)
	{
		offset = -(count * sizeof(v3));
		fseek(fd, offset, SEEK_END);
		if (read_state(fd, &v3, count - 1, 'd') == -1)
		{
			handle_error("input file read error!\n");
		}
		if (((count - 1) % 3 == 0 && v3.z < 0))
		{
			offset = -((count + 2) * sizeof(v3));
			count+=2;

			fseek(fd, offset, SEEK_END);
			break;
		}

		count++;
	}

	printf("\nLOAD LAST STEP:[%d]\n", count);

	if((arr->addr = (t_v3 *) malloc(count*3 * sizeof(t_v3)))==NULL){
		io_error("[Integrator: t_v3 *addr] allocate error!\n");
	}

	arr->len = count/3;
	arr->size = count;
	// count = 1;
	int ind = 0;
	while(count > 0){
		if (read_state(fd, &v3, count-1, 'd') == -1)
			{
				handle_error("input file read error!\n");
			}
			(arr->addr[ind]).x = v3.x;
			(arr->addr[ind]).y = v3.y;
			(arr->addr[ind]).z = v3.z;
			
			count--;
			ind++;

	}
	return fpos_end + offset + sizeof(t_v3);
}

void io_read_input(char **av, t_params *params, t_arrv3 *arr)
{
	FILE *fd;

	if ((fd = fopen(av[ARG_IO], "rb")) == NULL)
	{
		io_error("Cant open input file\n");
		return;
	}
	// params = (t_params *) malloc(1 * sizeof(t_params));
	read_params(fd, params);

	//x y z | vx vy vz |m q dp|
	int fpos = set_fd_to_last_step(fd, (arr));
	//load_last_step(fd, fpos, &(arr->addr));
	fclose(fd);

	//  t_v3 v3;
	//  read_state(fd, &v3, 0, 'a');
}

