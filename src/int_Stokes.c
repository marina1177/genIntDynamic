#include "../includes/verle.h"

static double Re[] = {0.471, 0.702, 0.896, 1.13, 1.38, 1.63, 2.19, 2.62, 3.03, 3.67, 4.4, 5.16, 6.27, 7.51, 8.95, 11.0, 13.3, 16.6, 21.2, 27.5, 35.2, 46.8, 62.3, 79.8, 98.2, 125, 159, 206, 254, 325, 411, 526, 656, 851, 1076, 1307, 1610, 2036, 2540, 3254, 3804, 4686, 6003};
static double Cd[] = {55.3, 37.6, 29.4, 23.4, 19.3, 16.3, 12.8, 11.0, 9.66, 8.26, 7.17, 6.31, 5.48, 4.75, 4.2, 3.63, 3.19, 2.76, 2.38, 2.04, 1.79, 1.56, 1.33, 1.19, 1.09, 0.967, 0.884, 0.797, 0.738, 0.684, 0.64, 0.609, 0.586, 0.564, 0.542, 0.529, 0.515, 0.502, 0.489, 0.483, 0.477, 0.471, 0.471};
static double Rho=1.2;

static double spline(double *X, double *Y, double xq){

}

void stokes(t_arrv3 *arr, t_v3 *fSt){
	double re;
	double v;
	double cd;

	double prt_rad = 0;

	for(int n = 0; n < arr->len; n++){

		prt_rad = arr->addr[n*3+2].z/2;
		if(prt_rad < 0)
			prt_rad *=-1;
		printf("Stokes[%d]: vx:%f; vy:%f; vz:%f\n", n, arr->addr[n*3+1].x, arr->addr[n*3+1].y, arr->addr[n*3+1].z);

		if(THREE_DIM == 1)
			v = sqrt(pow(arr->addr[n*3+1].x,2)+pow(arr->addr[n*3+1].y,2)+pow(arr->addr[n*3+1].z,2));
		else
			v = sqrt(pow(arr->addr[n*3+1].x,2)+pow(arr->addr[n*3+1].y,2));

		re = 2*prt_rad*v*Rho / NU_AIR;
	if(re > 0.47){
		printf("re[%f] > 0.47\n", re);
	// 	cd = spline(Re, Cd,re);
	// 	fSt->x = -0.5*cd*M_PI*pow(prt_rad,2)*Rho*pow(v,2)*v3[n*3+1].x/v;
	// 	fSt->y = -0.5*cd*M_PI*pow(prt_rad,2)*Rho*pow(v,2)*v3[n*3+1].y/v;
	// 	fSt->z = -0.5*cd*M_PI*pow(prt_rad,2)*Rho*pow(v,2)*v3[n*3+1].z/v;
	}
	//else{
		fSt->x = -6*M_PI*prt_rad*NU_AIR*arr->addr[n*3+1].x;
		fSt->y = -6*M_PI*prt_rad*NU_AIR*arr->addr[n*3+1].y;
		fSt->z = -6*M_PI*prt_rad*NU_AIR*arr->addr[n*3+1].z;
	// }
	printf("Stokes force[%d]: fx:%f; fy:%f; fz:%f\n", n, fSt[n].x, fSt[n].y, fSt[n].z);

	}
}
