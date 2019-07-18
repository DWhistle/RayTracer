#include "../incs/vector.h"
#include <math.h>

t_vec vec_fabs(t_vec vec)
{
    vec.arr[0] = fabs(vec.arr[0]);
    vec.arr[1] = fabs(vec.arr[1]);
    vec.arr[2] = fabs(vec.arr[2]);
    vec.arr[3] = fabs(vec.arr[3]);
    return (vec);
}

t_vec vec_fmin(t_vec vec, double n)
{
    vec.arr[0] = fmin(vec.arr[0], n);
    vec.arr[1] = fmin(vec.arr[1], n);
    vec.arr[2] = fmin(vec.arr[2], n);
    vec.arr[3] = fmin(vec.arr[3], n);
    return (vec);
}

t_vec vec_fmax(t_vec vec, double n)
{
    vec.arr[0] = fmax(vec.arr[0], n);
    vec.arr[1] = fmax(vec.arr[1], n);
    vec.arr[2] = fmax(vec.arr[2], n);
    vec.arr[3] = fmax(vec.arr[3], n);
    return (vec);
}