#ifndef VERLE_H
# define VERLE_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdint.h>
# include <limits.h>
# include <float.h>
# include <string.h>
# include <stdint.h>
# include <math.h>
# include <errno.h>

# include <stdio.h>

# include "constants.h"
# include "params.h"


# define ERR_ALLOC "Can\'t allocate memory"

typedef struct s_v3			t_v3;
typedef struct s_array_v3	t_arrv3;
typedef struct s_params		t_params;

struct			s_params
{
	int			amount_of_particles;
	double		freq;
	double		tfull; //все время расчета
	double		tstep;
	double		U; //ac
	double		nu; // вязкость вздуха

	double		da;
	double		ra;
	double		V; //dc

};

struct			s_array_v3
{
	int			len; // текущая длина массива(активные частицы)
	int			size; // максимальный размер массива
	t_v3*		addr;
};

struct			s_v3
{
	double		x;
	double		y;
	double		z;
};

//print_output.c
void			io_error(char *error_msg);


// mem_manage.c
void			malloc_tv3(int size, t_arrv3* tv3_arr, char * error_msg);

/*
** io_write_input.c
*/

/*
** gen_main.c
*/
int				gen_main();

/*
** main.c
*/
int				handle_error(char *s);

#endif
