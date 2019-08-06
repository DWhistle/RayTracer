#ifndef QUAT_H
# define QUAT_H
# ifndef __OPENCL_C_VERSION__
#  include <math.h>
# endif
#include "vector.h"

typedef struct	s_quat
{
	double		w;
	double		x;
	double		y;
	double		z;
}				t_quat;

t_quat			quat_from_vec(t_vec4 vec);
t_vec4			vec_from_quat(t_quat q);
t_quat			quat_invert(t_quat q);
t_quat			quat_scale(t_quat q, double val);
t_quat			quat_mul_vector(t_quat a, t_vec4 b);
t_quat			quat_mul_quat(t_quat a , t_quat b);
t_quat			create_quat(t_vec4 rotate_vector, double rotate_angle);
double			quat_length(t_quat q);

#endif
