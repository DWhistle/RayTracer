#include <math.h>
#include "ray_render.h"
#include "libft.h"
#include <stdio.h>

double			update_r(t_obj new_obj, t_vec point)
{
	double len;

	point = vec_sub(point, new_obj.point);
	point = rot(new_obj.rot_quat, point);
	if (new_obj.fract > 0)
	{
		point.arr[0] = fmod(point.arr[0], new_obj.fract) - new_obj.fract * 0.5;
		point.arr[1] = fmod(point.arr[1], new_obj.fract) - new_obj.fract * 0.5;
		point.arr[2] = fmod(point.arr[2], new_obj.fract) - new_obj.fract * 0.5;
	}
	len = new_obj.len(point, new_obj.param) - new_obj.rad;
	if (new_obj.ind == 1)
		len = fmax(len, -(2*point.arr[0] + point.arr[1]) / 2);
	return (len);
}

t_vec			get_normal(t_vec point, t_obj obj)
{
	double e = 0.0053;
	t_vec		vec;

	
	vec.arr[0] = (update_r(obj, vec_sum(point, new_vec3(e, 0, 0))) - update_r(obj, vec_sub(point, new_vec3(e, 0, 0))));
	vec.arr[1] = (update_r(obj, vec_sum(point, new_vec3(0, e, 0))) - update_r(obj, vec_sub(point, new_vec3(0, e, 0))));
	vec.arr[2] = (update_r(obj, vec_sum(point, new_vec3(0, 0, e))) - update_r(obj, vec_sub(point, new_vec3(0, 0, e))));
	vec.arr[3] = 0;
	if (obj.neg)
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

double			get_dist(int neg, t_obj **obj, t_vec point, t_scene scene)
{
	int		counter;
	double	r;
	double	dist;

	counter = 0;
	dist = scene.accuracy.max_dist + 1;
	while (counter != scene.number_objs)
	{
		if (neg == scene.objs[counter].neg && (!scene.ignore || scene.objs[counter].ind != scene.ignore->ind))
		{
			r = update_r(scene.objs[counter], point);
			if (r < dist)
			{
				dist = r;
				*obj = scene.objs + counter;
			}
		}
		counter++;
	}
	return (dist);
}

t_point_data	raymarching(t_scene objs, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
	double	r[2];
	t_obj	*obj;
	t_obj	*obj2;
	double	dist;
	t_vec	new_point;

	dist = 0;
	obj = 0;
	new_point = point;
	while (accuracy.depth_march-- &&
			dist < accuracy.max_dist)
	{
		
		r[0] = get_dist(0, &obj, new_point, objs);
		r[1] = get_dist(1, &obj2, new_point, objs);
		r[0] = fmax(r[0], -r[1]);
		if (r[0] != -r[1])
			obj2 = obj;
		if (r[0] < accuracy.delta)
		{
			return (crate_point_data(get_normal(new_point, *obj2), obj, new_point, new_vec0()));
		}
		dist += r[0];
		new_point = vec_sum(vec_dotdec(vec, dist), point);
	}
	return (crate_point_data(new_vec0(), 0, new_vec0(), new_vec0()));
}

t_point_data	shadowmarching(t_scene objs, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
	double	r[3];
	t_obj	*obj;
	t_obj	*obj2;
	double	dist;
	t_vec	new_point;

	dist = 0;
	obj = 0;
	new_point = point;
	r[2] = 1;
	objs.ignore = 0;
	while (accuracy.depth_march-- &&
			dist < accuracy.max_dist)
	{
		
		r[0] = get_dist(0, &obj, new_point, objs);
		r[1] = get_dist(1, &obj2, new_point, objs);
		r[0] = fmax(r[0], -r[1]);
		r[2] = fmin( r[2], 32*r[0] / dist);
		if (r[0] != -r[1])
			obj2 = obj;
		if (r[2] < accuracy.delta)
		{
			return (crate_point_data(get_normal(new_point, *obj2), obj, new_point, new_vec0()));
		}
		dist += fmax(r[0], accuracy.delta);
		new_point = vec_sum(vec_dotdec(vec, dist), point);
	}
	return (crate_point_data(new_vec0(), 0, new_vec0(), new_vec0()));
}
