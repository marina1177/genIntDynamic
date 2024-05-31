#include "../includes/verle.h"


void exception(int *exclude,  t_arrv3 *arr){
	double R = 0.145; //радиус при котором частица считается вылетевшей
    for(int i = 0; i<arr->len; i++){
		if(exclude[i]==0){
			continue;
		}
		if(pow(arr->addr[i*3].x,2)+pow(arr->addr[i*3].y,2) > pow(R,2) ||
			pow(arr->addr[i*3].x-0.01,2)+pow(arr->addr[i*3].y+0.01,2) < pow(0.002,2) ||
			pow(arr->addr[i*3].x-0.01,2)+pow(arr->addr[i*3].y-0.01,2) < pow(0.002,2) ||
			pow(arr->addr[i*3].x+0.01,2)+pow(arr->addr[i*3].y-0.01,2) < pow(0.002,2) ||
			pow(arr->addr[i*3].x+0.01,2)+pow(arr->addr[i*3].y+0.01,2) < pow(0.002,2)){
				exclude[i]=0;
				printf("\nEXCLUDED: #%d \n", i);
			}
	}
	for(int i = 0; i<arr->len; i++){
		if(pow(arr->addr[i*3].x,2)+pow(arr->addr[i*3].y,2) > 1.1*pow(R,2) ){
			arr->addr[i*3].x = R*0.9+rand()*R/100;
			arr->addr[i*3].y = R*0.9+rand()*R/100;
		}
	 }
}
