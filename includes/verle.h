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

int						g_n_pot;

typedef struct s_v3			t_v3;
typedef struct s_array_v3	t_arrv3;
typedef struct s_params		t_params;
typedef	struct s_map		t_map;

struct			s_map
{
	double		x;
	double		y;
	double		z;

	double		E;
};

struct			s_params
{
	double		amount_of_particles;
	double		tfull; //все время расчета
	double		tstep;//шаг расчета
	double		freq;
	double		U; //ac
	double		V; //dc

	double		da; // диаметр электродов
	double		ra;// рассояние между электродами
};

struct			s_array_v3
{
	int			len; // текущая длина массива(активные частицы)amount_of_particles
	int			size; // максимальный размер массива amount_of_particles*3
	t_v3*		addr;

};

// по 3 на каждую частицу
//| x y z| vx vy vz| m q dp|
struct			s_v3
{
	double		x;
	double		y;
	double		z;
};

// io_write_gradient.c
void			io_write_gradient_to_file(double *extremes,double Ex[g_n_pot][g_n_pot], double Ey[g_n_pot][g_n_pot]);
// io_write_output.c
void			io_write_to_outfile(FILE *fp, t_v3 *buffer, int size);
void			io_write_to_buffer(t_v3 *buffer, t_arrv3 *arr, int step_cnt);

//int_tension_for_particle.c
void			tension_for_particle(t_params *params, int *exclude,
				t_arrv3 *arr, double *extremes,
				double Ex[g_n_pot][g_n_pot], double Ey[g_n_pot][g_n_pot],
		 		double t, t_v3 *f_tr);

// interparticle_forces.c
void			interparticle_forces(t_arrv3 *arr, t_v3 *fC);

//int_Stokes.c
void			stokes(t_arrv3 *arr, t_v3 *fSt);

/*
** int_exception.c
*/
void			exception(int *exclude,  t_arrv3 *arr);

//int_acc_calc.c
void			acceleration_calc(t_v3 *acc, t_arrv3 *arr,
 				t_v3 *fSt, t_v3 *fC, t_v3 *f_tr);

// int_coord_calc.c
void			full_step_coord_calc(t_arrv3 *arr, double dt);

// int_velocity_calc.c
void			half_step_velocity_calc(t_v3 *acc, t_arrv3 *arr, double dt, int	*exclude);
void			full_step_velocity_calc(t_v3 *acc, t_arrv3 *arr, double dt, int	*exclude);

/*
** int_tension.c
*/
void			tension(t_map *map, double *extremes, double Ex[g_n_pot][g_n_pot], double Ey[g_n_pot][g_n_pot] );
void			get_extremes(t_map *map, int map_size, double *extremes);

/*
** io_read_map.c
*/
void			set_map_by_index(t_map * map, int ind, char* line);
int				io_read_map(char **av, t_map **map);

/*
** int_algo.c
*/
void			int_algo(char **av,t_params *params, t_arrv3 *arr, double *extremes, double Ex[g_n_pot][g_n_pot], double Ey[g_n_pot][g_n_pot]);

/*
** int_tools.c
*/
int				sum(int *intarray, int len);

/*
** int_main.c
*/
int				int_main(char **av);


//print_output.c
void			io_error(char *error_msg);

//int_mem_manage.c
t_map ** v3_2darray_alloc(size_t N, size_t M);

// mem_manage.c
void			malloc_tv3(int size, t_arrv3* tv3_arr, char * error_msg);

/*
** io_tools.c
*/
void 			print_state(t_v3 *v3, int indx, char order);
int				read_state(FILE *fp, t_v3 *v3, int indx, char order);
void			print_params(t_params *params);
void			read_params(FILE *fp, t_params *params);
void			read_initial_states(FILE *fp);

// ft_strsplit.c
char			**ft_strsplit(char const *s, char c);

/*
** io_read_input.c
*/
void			io_error(char *error_msg);
void			load_last_step(FILE *fd, int fpos, t_v3** addr);
int				set_fd_to_last_step(FILE *fd,  t_arrv3 *arr);
void			io_read_input(char **av, t_params *params,t_arrv3 *arr);

/*
** io_write_input.c
*/
void			io_write_input(char **av, t_params *params, t_arrv3	*arr);

/*
** gen_mem_manage.cx
*/
t_params		*params_malloc();
t_arrv3			*arrv3_malloc();
void			arrv3_free(t_arrv3 *arr);

/*
** gen_arrv3.c
*/
double			calc_particle_mass(double particle_diameter);
int				check_intersections(double *coords, int i);
double			randfrom(double min, double max);
void			set_coords(double *coords, int i);
void			set_velocity(t_v3 *vlct);
void			set_initial_values(t_arrv3 *arr);

/*
** gen_params.c
*/
void			set_default_params(t_params *params);

/*
** gen_main.c
*/
int				gen_main(char **av);

/*
** main.c
*/
int				handle_error(char *s);

#endif
