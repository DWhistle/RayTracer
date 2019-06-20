#include "ray_render.h"

double	len_circle(t_vec point, t_sphere *sphere)
{
	return (vec_len(vec_sub(point, sphere->point)) - sphere->r);
}

double	len_cone(t_vec point, t_cone *cone)
{
	double q;
	
	q = vec_len(vec_sub(cone->point, point));
	return (vec_dotvec(cone->vec, new_vec2(q, point.arr[2])));
}

double	len_cylinder(t_vec point, t_cylinder *cylinder)
{
	double	k;
	t_vec	vec;

	vec = vec_sub(point, cylinder->point);
	k = vec_dotvec(vec, cylinder->vec);
	return (vec_len(vec_sub(vec, vec_dotdec(cylinder->vec, k))) - cylinder->r);
}

double	len_plane(t_vec point, t_plane *plane)
{
	return (fabs(vec_dotvec(point, plane->norm) - vec_dotvec(plane->point, plane->norm)));
}
