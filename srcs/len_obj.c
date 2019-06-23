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

double	len_tor(t_vec point, t_tor *tor)
{
	double len;
	t_vec p;
	t_vec p2;
	t_vec vec;

	len = len_plane(point, &(tor->plane));
	p = vec_sum(point, vec_dotdec(vec_dotdec(tor->plane.norm, -1), len));
	p2 = vec_sum(point, vec_dotdec(tor->plane.norm, len));
	vec = vec_sub(tor->plane.point, p);
	if (vec_sqrdist(vec_sub(tor->plane.point, p)) < vec_sqrdist(vec_sub(tor->plane.point, p2)))
		vec = vec_sub(tor->plane.point, p);
	else
	{
		vec = vec_sub(tor->plane.point, p2);
		p = p2;
	}
	p = vec_sum(p, vec_dotdec(vec_norm(vec), vec_len(vec) - tor->R));
	return (vec_len(vec_sub(point, p)) - tor->r);
}
