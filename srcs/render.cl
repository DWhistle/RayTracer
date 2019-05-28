#include "objects.h"

double	len_circle(double3 point, t_sphere *sphere)
{
	return (fast_length(point - sphere->point) - sphere->r);
}

double	len_cone(double3 point, t_cone *cone)
{
	double q;
	
	q = fast_length(cone->point - point);
	return (dot(cone->vec, (double3)(q, point.arr[2], 0.0)));
}

double	len_cylinder(double3 point, t_cylinder *cylinder)
{
	double	k;
		vec;

	vec = point - cylinder->point;
	k = dot(vec, cylinder->vec);
	return (fast_length(vec - dot(cylinder->vec, k)) - cylinder->r);
}

double	len_plane(double3 point, t_plane *plane)
{
	return (fabs(plane->norm.arr[0] * point.arr[0] + \
			plane->norm.arr[1] * point.arr[1] + \
			plane->norm.arr[2] * point.arr[2] - \
			plane->norm.arr[0] * plane->point.arr[0] - \
			plane->norm.arr[1] * plane->point.arr[1] - \
			plane->norm.arr[2] * plane->point.arr[2]));
}


double			update_r(double r, t_obj new_obj, double3 point, t_scene objs, int n)
{
	double len;
    double3 p[n];
    
	len = 0;
    
	if (objs.ignore && objs.ignore->ind == new_obj.ind)
		return (r);
	if (new_obj.type == CIRCLE)
		len = len_circle(point, new_obj.obj);
	else if (new_obj.type == PLANE)
		len = len_plane(point, new_obj.obj);
	else if (new_obj.type == CYLINDER)
		len = len_cylinder(point, new_obj.obj);
	else if (new_obj.type == CONE)
		len = len_cone(point, new_obj.obj);
	if (r == -1 || len < r)
		r = len;
	return (r);
}

t_point_data	raymarching(t_scene objs, double3 vec,
							t_accuracy accuracy, double3 point)
{
	double	r;
	int		counter;
	double3	next_point;

	next_point = point;
	while (accuracy.depth_march-- &&
			fast_length(point - next_point) < accuracy.max_dist)
	{
		r = -1;
		counter = objs.number_objs;
		while (counter--)
		{
			r = update_r(r, objs.objs[counter], next_point, objs);
			if (r < accuracy.delta && r != -1)
				return (crate_point_data(get_normal(next_point, objs.objs[counter]), objs.objs + counter, next_point, (double3)(0.0, 0.0, 0.0)));
		}
		next_point = next_point + dot(vec, r);
	}
	return (crate_point_data((double3)(0.0, 0.0, 0.0), 0, (double3)(0.0, 0.0, 0.0), (double3)(0.0, 0.0, 0.0)));
}


t_point_data	path_tracing(t_scene scene, double3 vec,
							t_accuracy accuracy, double3 point)
{
	t_point_data	point_data;
	t_point_data	point_data2;
	int				depth_pt;
	double3			norm;

	depth_pt = 0;
	point_data = raymarching(scene, vec, accuracy, point);
	point_data2 = point_data;
	while (accuracy.depth_pt > depth_pt++ && point_data2.obj)
	{
		scene.ignore = point_data2.obj;
		norm = point_data2.norm;
		if (point_data2.obj && is_light(scene, point_data2.obj->ind))
		{
			scene.ignore = 0;
			point_data.color = dot(point_data.obj->color,
											1.0 / depth_pt);
			break ;
		}
		point_data2 = raymarching(scene, rand_vec(norm), accuracy, point);
	}
	return (point_data);
}

double3	ray_render(t_scene scene, double3 point, t_accuracy accuracy)
{
	int				depth_ref;
	t_point_data	point_data;
	t_point_data	*points;
	double3			color;
	double3			vec;

	vec = normalize(vec_sub(point, scene.cam));
	point_data = path_tracing(scene, vec, accuracy, scene.cam);
	if (point_data.obj)
	{
        //FIXME: сделать выделение статической памяти или посмотреть как выделять динамически
		points = malloc(sizeof(t_point_data) * (accuracy.depth_ref + 1));
		points[0] = point_data;
		depth_ref = 0;
		while (accuracy.depth_ref > depth_ref++ &&
		point_data.obj && point_data.obj->reflection)
		{
			scene.ignore = point_data.obj;
			point_data = path_tracing(scene,
			    get_ref_vec(point_data, vec), accuracy, point_data.point);
			points[depth_ref] = point_data;
		}
		scene.ignore = 0;
		return (f(points, depth_ref, scene));
	}
	return ((double3)(0.0, 0.0, 0.0));
}


double3	antialiasing(t_scene scene, double x, double y, t_accuracy accuracy)
{
	double2 d;
	double3 color_1;
	double3 color_2;

    
	color_1 = (double3)(0.0, 0.0, 0.0);
	color_2 = (double3)(0.0, 0.0, 0.0);
	d = (double2)(0.0, 0.0);
	scene.ignore = 0;
	while (x + d.x < x + 1)
	{
		d.y = 0;
		while (y + d.y < y + 1)
		{
			color_1 = color_1 + ray_render(scene, (double3)((x + d.x), (y + d.y), MAX_Z), accuracy));
			d.y += 1.0 / accuracy.rpp;
		}
		color_1 = dot(color_1, 1.0 / accuracy.rpp);
		color_2 = color_1 + color_2;
		d.x += 1.0 / accuracy.rpp;
	}
	return (dot(color_2, 1.0 / accuracy.rpp));
}
