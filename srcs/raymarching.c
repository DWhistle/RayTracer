#include <math.h>
#include "ray_render.h"
#include "libft.h"
#include <stdio.h>

double			update_r(t_obj new_obj, t_vec point)
{
	double len;

	point = vec_sub(point, new_obj.point);
	point = rot(new_obj.rot_quat, point);
	len = new_obj.len(point, new_obj.param) - new_obj.rad;
	return (len);
}

t_vec			get_normal(t_vec point, t_obj obj)
{
	double e = 0.0053;
	t_vec		vec;

	if (obj.type == SPHERE)
		printf("fefe\n");
	vec.arr[0] = (update_r(obj, vec_sum(point, new_vec3(e, 0, 0))) - update_r(obj, vec_sub(point, new_vec3(e, 0, 0))));
	vec.arr[1] = (update_r(obj, vec_sum(point, new_vec3(0, e, 0))) - update_r(obj, vec_sub(point, new_vec3(0, e, 0))));
	vec.arr[2] = (update_r(obj, vec_sum(point, new_vec3(0, 0, e))) - update_r(obj, vec_sub(point, new_vec3(0, 0, e))));
	vec.arr[3] = 0;
	if (obj.type == SPHERE)
		vec = vec_dotdec(vec, -1);
	return(vec_norm(vec));
}

t_point_data	crate_point_data(t_vec norm,
				t_obj *obj, t_vec point, t_vec color)
{
	t_point_data point_data;

	point_data.norm = norm;
	point_data.obj = obj;
	point_data.point = point;
	point_data.color = color;
	return (point_data);
}

t_point_data	raymarching(t_scene objs, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
	double	r;
	double r1;
	t_obj	*obj;
	double	dist;
	int		counter;
	t_vec	next_point;

	next_point = point;
	dist = 0;
	while (accuracy.depth_march-- &&
			vec_len(vec_sub(point, next_point)) < accuracy.max_dist)
	{
		r1 = accuracy.max_dist + 1;
		counter = objs.number_objs;
		while (counter--)
		{
			if (!objs.ignore || objs.objs[counter].ind != objs.ignore->ind)
			{
				r = update_r(objs.objs[counter], next_point);
				if (objs.objs[counter].type == SPHERE)
				{
					if (-r > r1)
					{
						obj = objs.objs + counter;
						r1 = -r;
					}
				}
				else
				{
					if (r < r1)
					{
						obj = objs.objs + counter;
						r1 = r;
					}
				}
			}
		}
		if (r1 < accuracy.delta)
		{
			return (crate_point_data(get_normal(next_point, *obj), objs.objs + 1, next_point, new_vec0()));
		}
		dist += r1;
		next_point = vec_sum(vec_dotdec(vec, dist), point);
	}
	return (crate_point_data(new_vec0(), 0, new_vec0(), new_vec0()));
}
