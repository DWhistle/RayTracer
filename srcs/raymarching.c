#include <math.h>
#include "ray_render.h"
#include "libft.h"
#include <stdio.h>
#include "SDL2/SDL.h"

t_vec			moving(t_obj obj, t_vec point)
{
	point = vec_sub(point, obj->point);
	point = rot(obj->angle, obj->rot_vec, point);
	return (point);
}

double			update_r(double r, t_obj *o, t_obj new_obj, t_vec point, t_scene objs)
{
	double len;

	point = moving(new_obj, point);
	len = -1;
	if (objs.ignore && objs.ignore->ind == new_obj.ind)
		return (r);
	if (new_obj.type == SPHERE)
		len = len_circle(point, new_obj.obj);
	else if (new_obj.type == PLANE)
		len = len_plane(point, new_obj.obj);
	else if (new_obj.type == CYLINDER)
		len = fabs(len_cylinder(point, new_obj.obj)) - 50;
	else if (new_obj.type == CONE)
		len = len_cone(point, new_obj.obj);
	else if (new_obj.type == TOR)
		len = len_tor(point, new_obj.obj);
	else if (new_obj.type == MOBIUS)
		len = len_mobius(point, new_obj.obj);
	else if (new_obj.type == BOX)
		len = len_box(point, new_obj.obj);
	else if (new_obj.type == CROSS)
		len = map(point, new_obj.obj);
	if (r == -1 || len < r)
	{
		//r = max(len, point.arr[1]);
		r = len;
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
			if (r < accuracy.delta)
			return (crate_point_data(get_normal(next_point,
			o, objs, r), objs.objs + counter, next_point, new_vec0()));
		}
		next_point = vec_sum(next_point, vec_dotdec(vec, r));
	}
	return (crate_point_data(new_vec0(), 0, new_vec0(), new_vec0()));
}
