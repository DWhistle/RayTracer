#include <math.h>
#include "ray_render.h"
#include "libft.h"
#include <stdio.h>
#include "SDL2/SDL.h"

double			update_r(double r, t_obj new_obj, t_vec point, t_scene objs)
{
	double len;

	len = -1;
	if (objs.ignore && objs.ignore->ind == new_obj.ind)
		return (r);
	if (new_obj.type == SPHERE)
		len = len_circle(point, new_obj.obj);
	else if (new_obj.type == PLANE)
		len = len_plane(point, new_obj.obj);
	else if (new_obj.type == CYLINDER)
		len = len_cylinder(point, new_obj.obj);
	else if (new_obj.type == CONE)
		len = len_cone(point, new_obj.obj);
	else if (new_obj.type == TOR)
		len = len_tor(point, new_obj.obj);
	else if (new_obj.type == MOBIUS)
		len = len_mobius(point, new_obj.obj);
	if (r == -1 || len < r)
		r = len;
	return (r);
}

t_vec			get_normal(t_vec point, t_obj obj, t_scene objs)
{
	double e = 0.01;
	t_vec		vec;
	double	k;

	if (obj.type == SPHERE)
		return (vec_norm(vec_sub(point, ((t_sphere*)obj.obj)->point)));
	else if (obj.type == PLANE)
		return (((t_plane*)obj.obj)->norm);
	else 
	{
		k = update_r(-1, obj, point, objs);
		vec.arr[0] = update_r(-1, obj, vec_sum(point, new_vec3(e, 0, 0)), objs);
		vec.arr[1] = update_r(-1, obj, vec_sum(point, new_vec3(0, e, 0)), objs);
		vec.arr[2] = update_r(-1, obj, vec_sum(point, new_vec3(0, 0, e)), objs);
		return(vec_norm(vec));
	}
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

	next_point = point;
	while (accuracy.depth_march-- &&
			vec_len(vec_sub(point, next_point)) < accuracy.max_dist)
	{
		r = -1;
		counter = objs.number_objs;
		while (counter--)
		{
			r = update_r(r, objs.objs[counter], next_point, objs);
			if (r < accuracy.delta && r != -1)
				return (crate_point_data(get_normal(next_point,
			objs.objs[counter], objs), objs.objs + counter, next_point, new_vec0()));
		}
		next_point = vec_sum(next_point, vec_dotdec(vec, r));
	}
	return (crate_point_data(new_vec0(), 0, new_vec0(), new_vec0()));
}
