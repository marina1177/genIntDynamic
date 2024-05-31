#include "../includes/verle.h"

static void min_pot(t_map *map, int map_size,  double *extremes){

	double minX = map[0].x;
	double minY = map[0].y;
	double minZ = map[0].z;

	for(int i=0; i<map_size; i++){
		if(map[i].x<minX){
			minX=map[i].x;
		}
		if(map[i].y<minY){
			minY=map[i].y;
		}

		if(THREE_DIM == 1 && map[i].z<minZ){
			minZ=map[i].z;
		}
	}
	printf("minX:%.4f	minY:%.4f\n",minX, minY);
	(extremes)[0] = minX;
	(extremes)[1] = minY;
	if(THREE_DIM == 1)
		(extremes)[2] = minZ;


}

static void max_pot(t_map *map, int map_size, double *extremes){

	double maxX = map[0].x;
	double maxY = map[0].y;
	double maxZ = map[0].z;

	for(int i=0; i<map_size; i++){
		if(map[i].x > maxX){
			maxX=map[i].x;
		}
		if(map[i].y > maxY){
			maxY=map[i].y;
		}

		if(THREE_DIM == 1 && map[i].z > maxZ){
			maxZ=map[i].z;
		}
	}

	(extremes)[3] = maxX;
	(extremes)[4] = maxY;
	if(THREE_DIM == 1)
		(extremes)[5] = maxZ;
	printf("maxX:%.4f	maxY:%.4f\n",maxX, maxY);
}

static void gradient(double pot_matrix[g_n_pot][g_n_pot][3], double *extremes, double Ex[g_n_pot][g_n_pot], double Ey[g_n_pot][g_n_pot] ){

	double n_pot = extremes[6];
	double h_pot = extremes[7];

	for(int i = 0; i < n_pot; i++){
		for(int j = 0; j < n_pot; j++){

			if(j == 0){
				Ex[i][j]= (pot_matrix[i][j+1][3] - pot_matrix[i][j][3])/(h_pot);
			}
			else if(j == n_pot-1){
				Ex[i][j]= (pot_matrix[i][j][3] - pot_matrix[i][j-1][3])/(h_pot);
			}
			else
				Ex[i][j]= (pot_matrix[i][j+1][3] - pot_matrix[i][j-1][3])/(2*h_pot);
			//printf("|[%d,%d] %f  ", i, j,Ex[i][j]);

			if(i == 0){
				Ey[i][j]= (pot_matrix[i+1][j][3] - pot_matrix[i-1][j][3])/(h_pot);
			}
			else if(i == n_pot-1){
				Ey[i][j] = (pot_matrix[i][j][3] - pot_matrix[i-1][j][3])/(h_pot);
			}
			else
				Ey[i][j]= (pot_matrix[i+1][j][3] - pot_matrix[i-1][j][3])/(2*h_pot);

		}
		//printf("\n");
	}
//G(:,j) = 0.5*(A(:,j+1) - A(:,j-1));
}


void tension(t_map *map, double *extremes, double Ex[g_n_pot][g_n_pot], double Ey[g_n_pot][g_n_pot] ){

	int n_pot = 0;
	double h_pot = 0;
	double 	mins[3] = {0};
	double	maxes[3] = {0};

	n_pot = extremes[6];
	h_pot = extremes[7];
	printf("y0:%f, y1:%f\n",map[0].y, map[1].y );
	printf("n_pot:%d, h_pot:%f\n", n_pot, h_pot);

//!TODO  для 3 осей + k(z)
	double pot_matrix[n_pot][n_pot][3];// = {0};
	for(int i = 0; i < n_pot; i++){
		for(int j = 0; j < n_pot; j++){

		pot_matrix[i][j][1]= (double)map[(j)*n_pot+i].x;  //создание трехмерного массива
		pot_matrix[i][j][2]=(double)map[(j)*n_pot+i].y;   //координаты точки и потенциал
		pot_matrix[i][j][3]=(double)map[(j)*n_pot+i].E;
		}
	}

	gradient(pot_matrix, extremes, Ex, Ey);


	if(WRITE_GRAD == 1)
		io_write_gradient_to_file( extremes, Ex, Ey);

}

void get_extremes(t_map *map, int map_size, double *extremes){
	int n_pot = 0;
	double h_pot = 0;
	double 	mins[3] = {0};
	double	maxes[3] = {0};

	n_pot = sqrt(map_size);
	g_n_pot = n_pot;
	h_pot = map[1].y - map[0].y;
	//printf("y0:%f, y1:%f\n",map[0].y, map[1].y );
	printf("n_pot:%d, h_pot:%f\n", n_pot, h_pot);

	//Xmin | Ymin | Zmin
	min_pot(map, map_size, extremes);

	//Xmax | Ymax | Zmax
	max_pot(map, map_size, extremes);
	extremes[6] = n_pot;
	extremes[7] = h_pot;
}



