#include <math.h>
#include "ray_render.h"
#include "libft.h"
#include <stdio.h>
#include "SDL2/SDL.h"

t_vec			rand_point(t_vec point)
{
	t_vec	v;

	v = new_vec3(0, 0, 0);
	v.arr[0] = (rand() % 1000) * (rand() % 2 - 0.5) * 2;
	v.arr[1] = (rand() % 1000) * (rand() % 2 - 0.5) * 2;
	v.arr[2] = (rand() % 1000) * (rand() % 2 - 0.5) * 2;
	v = vec_norm(v);
    v = vec_dotdec(v, 40);
	point = vec_sum(point, v);
	return (point);
}

t_vec   lightt(t_scene objs, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
    t_point_data point_data;
    t_point_data shadow;
    double i;
    double n_dot_l;
    t_vec li;
    int j;
    t_vec color;

    j = 300;
    color = new_vec0();
    point_data = raymarching(objs, vec, accuracy, point);
    if (!point_data.obj)
            return (new_vec0());
    while(j--)
    {
        i = 0.1;
        li = vec_sub(rand_point(new_vec3(50, 0, 0)), point_data.point);
        accuracy.max_dist = vec_len(li);
        objs.ignore = point_data.obj;
        shadow = raymarching(objs, vec_norm(li), accuracy, point_data.point);
        n_dot_l = vec_dotvec(point_data.norm, li);
        if (n_dot_l > 0 && !shadow.obj)
            i += (n_dot_l / vec_len(li));
        color = vec_sum(color, vec_dotdec(point_data.obj->color, i));
    }
    color = vec_dotdec(color, 1.0/300);
    return (color);
}
