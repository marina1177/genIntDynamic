#include "../includes/verle.h"

void acceleration_calc(t_v3 *acc, t_arrv3 *arr,
  t_v3 *fSt, t_v3 *fC, t_v3 *f_tr){

	t_v3 F;
	for(int n =0; n < arr->len; n++){
		F.x = fSt[n].x + fC[n].x + f_tr[n].x;
		F.y = fSt[n].y + fC[n].y + f_tr[n].y;
		printf("[%d] Fx:%.20f;	Fy:%.20f; M[%d]:%.20f\n", n, F.x, F.y, n*3 + 2, arr->addr[n*3 + 2].x );
		acc[n].x = (fSt[n].x + fC[n].x + f_tr[n].x) / arr->addr[n*3 + 2].x ;
		acc[n].y = (fSt[n].y + fC[n].y + f_tr[n].y ) / arr->addr[n*3 + 2].x;
		acc[n].y -= G_CONST;
		printf("[%d] acc.x:%f; acc.y:%f\n", n, acc[n].x, acc[n].y);
	}
}
