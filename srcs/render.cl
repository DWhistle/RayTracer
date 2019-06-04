#include "objects.h"
#include "vec_mul.c"
#include "vec_sum.c"
#include "vector.c"

t_vec			rand_vec(t_vec vec)
{
	if (vec.arr[0] == 0)
		vec.arr[0] = (rand() % 200000 + 1) * ((double)(rand() % 2) - 0.5);
	else
		vec.arr[0] = (rand() % 100000 + 1) * vec.arr[0];
	if (vec.arr[1] == 0)
		vec.arr[1] = (rand() % 200000 + 1) * ((double)(rand() % 2) - 0.5);
	else
		vec.arr[1] = (rand() % 100000 + 1) * vec.arr[1];
	if (vec.arr[2] == 0)
		vec.arr[2] = (rand() % 200000 + 1) * ((double)(rand() % 2) - 0.5);
	else
		vec.arr[2] = (rand() % 100000 + 1) * vec.arr[2];
	return (vec_norm(vec));
}

int				is_light(t_scene scene, int ind)
{
	int counter;

	counter = 0;
	while (counter != scene.number_lights)
	{
		if (scene.lights[counter].ind == ind)
			return (1);
		counter++;
	}
	return (0);
}

t_point_data	path_tracing(t_scene scene, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
	t_point_data	point_data;
	t_point_data	point_data2;
	int				depth_pt;
	t_vec			norm;

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
			point_data.color = vec_dotdec(point_data.obj->color,
											1.0 / depth_pt);
			break ;
		}
		point_data2 = raymarching(scene, rand_vec(norm), accuracy, point);
	}
	return (point_data);
}

t_vec	get_ref_vec(t_point_data point_data, t_vec vec)
{
	vec = vec_dotdec(vec, -1);
	vec = vec_sub(vec_dotdec(point_data.norm,
	vec_dotvec(point_data.norm, vec) * 2), vec);
	vec = vec_norm(vec);
	return (vec);
}

t_vec	get_ref_color(t_point_data *points)
{
	int		i;
	t_vec	color_ref;
	t_vec	color;
	double	ref;

	i = 0;
	while (points[i].obj)
		i++;
	while (i-- != 1)
	{
		color_ref = points[i].color;
		ref = points[i - 1].obj->reflection;
		color = points[i - 1].color;
		color = vec_sum(vec_dotdec(color, 1 - ref), vec_dotdec(color_ref, ref));
		points[i - 1].color = color;
	}
	return (points[0].color);
}

t_vec	f(t_point_data *points, int depth_ref, t_scene scene)
{
	t_vec			color;

	points[depth_ref].obj = 0;
	color = get_ref_color(points);
	free(points);
	scene.ignore = 0;
	return (color);
}

t_vec	ray_render(t_scene scene, t_vec point, t_accuracy accuracy)
{
	int				depth_ref;
	t_point_data	point_data;
	t_point_data	*points;
	t_vec			vec;

	vec = vec_norm(vec_sub(point, scene.cam));
	point_data = path_tracing(scene, vec, accuracy, scene.cam);
	if (point_data.obj)
	{
		points = ft_memalloc(sizeof(t_point_data) * (accuracy.depth_ref + 1));
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
	return (vec);
}

t_vec	antialiasing(t_scene scene, double x, double y, t_accuracy accuracy)
{
	double	d_x;
	double	d_y;
	t_vec	color_1;
	t_vec	color_2;

	color_1 = new_vec0();
	color_2 = new_vec0();
	d_x = 0;
	scene.ignore = 0;
	while (x + d_x < x + 1)
	{
		d_y = 0;
		while (y + d_y < y + 1)
		{
			color_1 = vec_sum(color_1, ray_render(scene,
			new_vec3((x + d_x), (y + d_y), MAX_Z), accuracy));
			d_y += 1.0 / accuracy.rpp;
		}
		color_1 = vec_dotdec(color_1, 1.0 / accuracy.rpp);
		color_2 = vec_sum(color_1, color_2);
		d_x += 1.0 / accuracy.rpp;
	}
	return (vec_dotdec(color_2, 1.0 / accuracy.rpp));
}
