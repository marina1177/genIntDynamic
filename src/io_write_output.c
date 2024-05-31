#include "../includes/verle.h"


void io_write_to_buffer(t_v3 *buffer, t_arrv3 *arr, int step_cnt){
	printf("io_write_to_buffer: step_cnt=%d; arr-size=%d;\n", step_cnt, arr->size);
	int start = step_cnt*arr->size;
	for(int k =0; k < arr->size; k++){
		// if(k = 2 && arr->addr[k].z > 0)
		// 	arr->addr[k].z *=-1;
		buffer[start+k].x = arr->addr[k].x;
		buffer[start+k].y = arr->addr[k].y;
		buffer[start+k].z = arr->addr[k].z;
		//printf("[%d]:buf.x:%f; buf.y:%f; buf.z:%f\n", start+k,buffer[start+k].x, buffer[start+k].y, buffer[start+k].z);
		}
}

void io_write_to_outfile(FILE *fp, t_v3 *buffer, int size){

	if(size == 0){
		printf("Amount of steps to write outputfile is zero! Nothing to wrote.\n");
		return;
	}

	fseek(fp, 0, SEEK_END);
	//printf("amount_of_steps = %d; \n", amount_of_steps);
	for(int i = 0; i < size; i++){
		//printf("write [%d]	x: %9f,		y: %9f,		z: %9f\n", i, buffer[i].x, buffer[i].y, buffer[i].z);
		fwrite(&(buffer[i]),sizeof(t_v3), 1, fp);
	}

}
