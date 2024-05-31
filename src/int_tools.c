

int sum(int *intarray, int len){

	int sum = 0;
	for(int i = 0; i < len; i++){
		sum += intarray[i];
	}
	return sum;
}
