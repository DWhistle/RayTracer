#include "ray_render.h"

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
			new_vec3((x + d_x), (y + d_y), 150), accuracy));
			d_y += 1.0 / accuracy.rpp;
		}
		color_1 = vec_dotdec(color_1, 1.0 / accuracy.rpp);
		color_2 = vec_sum(color_1, color_2);
		d_x += 1.0 / accuracy.rpp;
	}
	return (vec_dotdec(color_2, 1.0 / accuracy.rpp));
}
