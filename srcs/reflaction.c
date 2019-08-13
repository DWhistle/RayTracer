#include "ray_render.h"
#include "libft.h"

t_vec			get_ref_vec(t_point_data point_data, t_vec vec)
{
	vec = vec_dotdec(vec, -1);
	vec = vec_sub(vec_dotdec(point_data.norm,
	vec_dotvec(point_data.norm, vec) * 2), vec);
	vec = vec_norm(vec);
	return (vec);
}

t_vec			get_ref_color(t_point_data *points)
{
	int		i;
	t_vec	color_ref;
	t_vec	color;
	double	ref;

	i = 0;
	while (points[i].obj)
		i++;
	points[i - 1].color = get_color_obj(points[i - 1]);
	while (i-- >= 2)
	{
		color_ref = points[i].color;
		ref = points[i - 1].obj->reflection;
		color = get_color_obj(points[i - 1]);
		color = vec_sum(vec_dotdec(color, 1 - ref), vec_dotdec(color_ref, ref));
		points[i - 1].color = color;
	}
	return (points[1].color);
}

t_vec			f(t_point_data *points, int depth_ref)
{
	t_vec			color;

	points[depth_ref + 1].obj = 0;
	if (!points)
		return (new_vec0());
	color = get_ref_color(points);
	free(points);
	return (color);
}

t_point_data	ray_render(t_scene *scene, t_vec vec,\
							t_vec point, t_point_data (*raymarch)())
{
	int				depth_ref;
	t_point_data	point_data;
	t_point_data	*points;

	point_data = raymarch(scene, vec, scene->accuracy, point);
	if (point_data.obj && point_data.obj->reflection > 0 && scene->accuracy.depth_ref)
		if ((points = ft_memalloc(sizeof(t_point_data) *\
			(scene->accuracy.depth_ref + 1))))
		{
			points[0] = point_data;
			depth_ref = 0;
			while (scene->accuracy.depth_ref > depth_ref++ &&\
					point_data.obj->reflection > 0)
			{
				vec = get_ref_vec(point_data, vec);
				points[depth_ref] = shadowmarching(scene,
					point, scene->accuracy, point_data.point);
			}
			point_data.ref_color = f(points, depth_ref);
			point_data.ref_point = points[depth_ref].point;
		}
	if (point_data.obj)
		point_data.color = get_color_obj(point_data);
	return (point_data);
}
