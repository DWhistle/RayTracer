#include <math.h>
#include "ray_render.h"
#include "libft.h"
#include <stdio.h>

double			mix(double x, double y, double a)
{
	return (x * (1 - a) + y * a);
}

double opSmoothUnion( double d1, double d2, double k )
{
	double h = clamp1( 0.5 + 0.5*(d2-d1)/k, 0.0, 1.0 );
	return mix( d2, d1, h ) - k*h*(1.0-h);
}

double			update_restriction(double r, t_obj obj, t_vec point)
{
	t_vec	norm;
	int		n;
	t_vec	new_point;

	if (!obj.restriction)
		return (r);
	n = obj.numbers_plane;
	while (n--)
	{
		norm = obj.restriction[n].norm;
		new_point = vec_sum(point, obj.restriction[n].dislocation);
		r = fmax(r, new_point.arr[0] * norm.arr[0] +\
						new_point.arr[1] * norm.arr[1] +\
						new_point.arr[2] * norm.arr[2]);
	}
	return (r);
}

double displace(t_vec point, double r, t_obj obj)
{
    return (r + sin(obj.frequency * point.arr[0]) * sin(obj.frequency * point.arr[2]) * sin(obj.frequency * point.arr[1]) * obj.amplitude);
}

double			onion(double len, double h)
{
	return (fabs(len) - h);
}

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
	len = new_obj.len(point, new_obj.param);
	len = update_restriction(len, new_obj, point);
	len = displace(point, len, new_obj);
	return (len - new_obj.rad);
}

t_vec			normal_map(t_vec point, t_obj obj)
{
    point = rot(obj.rot_quat, vec_sub(point, obj.point));
    if (obj.normal_map.texture)
    {
        if (obj.type == SPHERE)
            return (get_pixel(get_uv_spehere(&obj, point), obj.normal_map));
        if (obj.type == CYLINDER)
            return (get_pixel(get_uv_cylinder(&obj, point), obj.normal_map));
        if (obj.type == CONE)
            return (get_pixel(get_uv_cone(&obj, point), obj.normal_map));
        if (obj.type == PLANE)
            return (get_pixel(get_uv_plane(&obj, point), obj.normal_map));
    }
    return (new_vec0());
}

t_vec			get_normal(t_vec point, t_obj obj)
{
	double e = 0.0053;
	t_vec		vec;

	if (obj.normal_map.texture)
	{
		vec = vec_norm(normal_map(point, obj));
		vec = vec_dotdec(vec, -1);
		return (vec);
	}
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
				//dist = opSmoothUnion(r, dist, 50);
				dist = r;
				*obj = scene.objs + counter;
			}
		}
		counter++;
	}
	return (dist);
}

t_point_data	raymarch_in_obj(t_obj *obj, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
	double	r[2];
	double	dist;
	t_vec	new_point;

	dist = 0;
	new_point = point;
	new_point = vec_sum(vec_dotdec(vec, accuracy.delta * 2), point);
	while (accuracy.depth_march-- &&
			dist < accuracy.max_dist)
	{
		r[0] = fabs(update_r(*obj, point));
		if (r[0] < accuracy.delta)
		{
			dist += r[0] * 2;
			new_point = vec_sum(vec_dotdec(vec, dist), point);
			return (crate_point_data(get_normal(new_point, *obj), obj, new_point, new_vec0()));
		}
		dist += r[0];
		new_point = vec_sum(vec_dotdec(vec, dist), point);
	}
	return (crate_point_data(new_vec0(), 0, new_vec0(), new_vec0()));
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
	while (accuracy.depth_march-- &&
			dist < accuracy.max_dist)
	{
		r[0] = get_dist(0, &obj, new_point, objs);
		r[1] = get_dist(1, &obj2, new_point, objs);
		r[0] = fmax(r[0], -r[1]);
		r[2] = fmin( r[2], r[0] / dist);
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
