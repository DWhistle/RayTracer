#include "ray_render.h"
#include "libft.h"

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

t_point_data	ray_render(t_scene scene, t_vec point, t_accuracy accuracy, t_point_data (*raymarch)())
{
	int				depth_ref;
	t_point_data	point_data;
	t_point_data	*points;

	point_data = raymarch(scene, point, accuracy, scene.cam);
	if (point_data.obj)
	{
		points = ft_memalloc(sizeof(t_point_data) * (accuracy.depth_ref + 1));
		points[0] = point_data;
		depth_ref = 0;
		while (accuracy.depth_ref > depth_ref++ &&
		point_data.obj && point_data.obj->reflection)
		{
			point = get_ref_vec(point_data, point);
			point_data = shadowmarching(scene,
					point, accuracy, point_data.point);
			points[depth_ref] = point_data;
		}
		scene.ignore = 0;
		point_data.color = f(points, depth_ref, scene);
		return (point_data);
	}
	return (point_data);
}
