//#include "srcs/vector.c"
#include "incs/ray_rander_cl.h"
///#include "incs/objects.h"
//#include "srcs/vec_sum.c"
//#include "srcs/len_obj.c"
//#include "srcs/vec_mul.c"
//#include "srcs/vec_math.c"

t_vec	antialiasing(__global t_scene *scene, double x, double y, t_accuracy accuracy, t_point_data *point_data)
{
	t_vec	color_2;
	color_2 = new_vec0();	
	
	return (color_2);
}

__kernel void	ray_tracing(__global t_scene *scene,\
							__global t_light *lights,\
							__global t_obj *obj,\
							__global int *pixels, \
							__global t_point_data *points_data, \
							__global t_vec *scene_color)
{
	int			x;
	int			y;
	t_vec		color;
	int			i = get_global_id(0);

	x = i % scene->w;
	y = i / (scene->h*2);

	scene->lights = (t_light*)lights;
	scene->objs = (t_obj*)obj;
	scene->color = (t_vec*)scene_color;
	scene->points_data = (t_point_data*)points_data;
	color = antialiasing(scene, (double)x / scene->w - 0.5,
	(double)y / scene->h - 0.5, scene->accuracy, scene->points_data + x + scene->w * y);
	if (color.arr[0] > 255)
	{
		color.arr[1] += color.arr[0] - 255;
		color.arr[0] = 255;
	}
	if (color.arr[1] > 255)
	{
		color.arr[2] += color.arr[1] - 255;
		color.arr[1] = 255;
	}
	if (color.arr[2] > 255)
	{
		color.arr[0] += color.arr[2] - 255;
		color.arr[2] = 255;
	}
	if (color.arr[0] > 255)
		color.arr[0] = 255;
	if (scene->accuracy.depth_pt == 1)
		scene->color[x + scene->w * y] = color;
	else
		scene->color[x + scene->w * y] = vec_sum(scene->color[x + scene->w * y], color);
	color = vec_dotdec(scene->color[x + scene->w * y], 1.0 / scene->accuracy.depth_pt);
	pixels[x + scene->w * y] = (int)(color.arr[0]) << 16 |
			(int)(color.arr[1]) << 8 | (int)(color.arr[2]) | 0xff << 24;
}
