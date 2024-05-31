#include "../includes/verle.h"


void	set_map_by_index(t_map * map, int ind, char* line){

	char ** split;

	split = ft_strsplit(line, ' ') ;
	if(TWO_DIM == 1){
		map[ind].x = atof(split[0]);
		map[ind].y = atof(split[1]);
		map[ind].E = atof(split[2]);
	}
	else if(THREE_DIM == 1){
		map[ind].x = atof(split[0]);
		map[ind].y = atof(split[1]);
		map[ind].z = atof(split[2]);
		map[ind].E = atof(split[3]);
	}
	else{
		handle_error("Dimension flag [params.h] is not selected!\n ");
	}
	// printf("map[%d]:\n %.18f	%.18f	%.18f \n", ind, map[ind].x, map[ind].y, map[ind].E);

}

int io_read_map(char **av, t_map **map)
{
	int lines_count = 0;
	FILE *fd;

	if ((fd = fopen(av[ARG_MAP], "r")) == NULL)
	{
		io_error("Cant open map file\n");
		return 0;
	}
	while(! feof(fd)) {
         fscanf(fd, "%*[^\n]%*c");
         lines_count++;
   }

	*map = (t_map *)malloc(lines_count*sizeof(t_map));

	t_map *ptr = *map;

	fseek(fd, 0, SEEK_SET);
	char * line = NULL;
	size_t len = 0;
    ssize_t read;

	int i = 0;
	while ((read = getline(&line, &len, fd)) != -1) {
		// printf("Retrieved line of length %zu:\n", read);
		// printf("%s", line);

		set_map_by_index(ptr, i,line);
		//  printf("map[%d]:\n %.18f	%.18f	%.18f \n", i, map[i].x, map[i].y, map[i].E);

		i++;
	}
	fclose(fd);

	printf("line counts: %d\n", i);

	return i;
}
