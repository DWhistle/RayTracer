#include "ray_render.h"

t_vec	color_ipdate(t_scene *scene, t_vec color)
{
	return (vec_dotdec(color, 1.0 / scene->accuracy.rpp));
}

t_vec	antialiasing(t_scene *scene, double x,\
					double y, t_point_data *point_data)
{
	double	d_x;
	double	d_y;
	t_vec	color_1;
	t_vec	color_2;
	t_vec	vec;

	color_1 = new_vec0();
	color_2 = new_vec0();
	d_x = 0;
	while (x + d_x < x + 1.0 / scene->w)
	{
		d_y = 0;
		while (y + d_y < y + 1.0 / scene->h)
		{
			vec = vec_norm(new_vec3((x + d_x), (y + d_y),\
			(scene->FOW / 2) * scene->signz));
			vec = rot(scene->rot, rot(scene->rot_x, vec));
			color_1 = vec_sum(color_1,\
			lightt(scene, vec, scene->accuracy, point_data));
			d_y += 1.0 / scene->accuracy.rpp / scene->h;
		}
		color_2 = vec_sum(color_ipdate(scene, color_1), color_2);
		d_x += 1.0 / scene->accuracy.rpp / scene->w;
	}
	return (vec_dotdec(color_2, 1.0 / scene->accuracy.rpp));
}
