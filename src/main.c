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

	char	process_name[11];
	int		status;

	status = 0;
	if(strcmp(av[1], "-g") == 0){
		strcpy(process_name, "generator");
		printf("start %s: \n", process_name);

		status = gen_main();

	}else if(strcmp(av[1], "-i")== 0){
		strcpy(process_name, "integrator");
		printf("start %s: \n", process_name);

		//status = int_main();
	}

	if(status < 0){
		printf("%s",process_name); printf(" process is failed!\n");
		exit(0);
	}
	return 0;
}
