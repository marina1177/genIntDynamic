#include "../includes/verle.h"

int			handle_error(char *s)
{
	printf("%s\n", s);
	exit(1);
}



int		main(int ac, char **av)
{
	t_arrv3	crds;
	t_arrv3	vlcts;
	t_arrv3	props;

	FILE *fp;
	t_v3 v3;

	char	process_name[11];
	int		status;

	status = 0;
	if(strcmp(av[1], "-g") == 0){
		strcpy(process_name, "generator");
		printf("start %s: \n", process_name);

		status = gen_main(av);

		// t_params *params = malloc(sizeof(t_params));
		// fp = fopen(av[2],"rb");
		// read_params(fp, params);
		// read_initial_states(fp);
		// fclose(fp);

	}else if(strcmp(av[1], "-i")== 0){
		strcpy(process_name, "integrator");
		printf("start %s: \n", process_name);

		status = int_main(av);

		// t_params *params = malloc(sizeof(t_params));
		// fp = fopen(av[2],"rb");
		// read_params(fp, params);
		// read_initial_states(fp);

		// for(int indx = 0; indx < TMP_MAX/TIME_STEP;indx++ ){
		// read_state(fp, &v3, indx, 'a');

		// }
		// fclose(fp);
	}

	if(status < 0){
		printf("%s",process_name); printf(" process is failed!\n");
		exit(0);
	}
	return 0;
}
