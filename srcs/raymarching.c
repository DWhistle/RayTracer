#include <math.h>
#include "ray_render.h"
#include "libft.h"
#include <stdio.h>

double			update_r(double r, t_obj *o, t_obj new_obj, t_vec point, t_scene objs)
{
	double len;

	point = vec_sub(point, new_obj.point);
	point = rot(new_obj.angle, new_obj.rot_vec, point);
	len = -1;
	objs.objs = 0;
	if (objs.ignore && objs.ignore->ind == new_obj.ind)
		return (r);
	len = new_obj.len(point, new_obj.param);
	if (r == -1 || len < r)
	{
		r = len - new_obj.rad;
		*o = new_obj;
	}
	return (r);
}

t_vec			get_normal(t_vec point, t_obj obj, t_scene objs, double k)
{
	double e = 0.0053;
	t_vec		vec;
	t_obj		o;
	k = 0;
	vec.arr[0] = (update_r(-1, &o, obj, vec_sum(point, new_vec3(e, 0, 0)), objs) - update_r(-1, &o, obj, vec_sub(point, new_vec3(e, 0, 0)), objs));
	vec.arr[1] = (update_r(-1, &o, obj, vec_sum(point, new_vec3(0, e, 0)), objs) - update_r(-1, &o, obj, vec_sub(point, new_vec3(0, e, 0)), objs));
	vec.arr[2] = (update_r(-1, &o, obj, vec_sum(point, new_vec3(0, 0, e)), objs) - update_r(-1, &o, obj, vec_sub(point, new_vec3(0, 0, e)), objs));
	vec.arr[3] = 0;
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
	int		counter;
	t_vec	next_point;
	t_obj	o;

	next_point = point;
	while (accuracy.depth_march-- &&
			vec_len(vec_sub(point, next_point)) < accuracy.max_dist)
	{
		r = -1;
		counter = objs.number_objs;
		while (counter--)
		{
			r = update_r(r, &o, objs.objs[counter], next_point, objs);
			if (r < accuracy.delta && r != -1)
			{
				return (crate_point_data(get_normal(next_point, o, objs, r), objs.objs + counter, next_point, new_vec0()));
			}
		}
		next_point = vec_sum(next_point, vec_dotdec(vec, r));
	}
	return (crate_point_data(new_vec0(), 0, new_vec0(), new_vec0()));
}
