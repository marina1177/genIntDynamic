#include "../includes/verle.h"


t_map ** v3_2darray_alloc(size_t N, size_t M)
{
    t_map **A = (t_map **)malloc(N*sizeof(t_map *));
    for(int i = 0; i < N; i++) {
        A[i] = (t_map *)malloc(M*sizeof(t_map));
    }
    return A;
}
