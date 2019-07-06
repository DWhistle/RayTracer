#include "ray_render.h"

double	len_circle(t_vec point, t_sphere *sphere)
{
	return (vec_len(vec_sub(point, sphere->point)) - sphere->r);
}

double	len_cone(t_vec point, t_cone *cone)
{
	t_vec vec;
	t_vec vec1;
	double f;
	double s;	

	vec = vec_sub(point, cone->point);
	vec = vec_mul(cone->vec, vec);
	vec = vec_norm(rot(cone->angle, vec_norm(vec), cone->vec));
	f = fabs(vec_dotvec(vec_sub(cone->point, point), vec));
	vec1 = vec_norm(rot(-cone->angle, vec_norm(vec), cone->vec));
	s = fabs(vec_dotvec(vec_sub(cone->point, point), vec1));
	if (f < s)
		return (f);
	else
		return (s);
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

double	len_segment(t_segment segment, t_vec point)
{
	t_vec	vec1;
	t_vec	vec2;
	t_vec	vec3;

	vec1 = vec_sub(segment.b, segment.a);
	vec2 = vec_sub(point, segment.a);
	vec3 = vec_sub(point, segment.b);
	if (vec_dotvec(vec_norm(vec1), vec_norm(vec2)) < 0)
		return(vec_len(vec2));
	else if (vec_dotvec(vec_dotdec(vec_norm(vec1), -1), vec_norm(vec3)) < 0)
		return(vec_len(vec3));
	else
	{
		if(vec_len(vec_mul(vec_norm(vec1), vec2)) < 1)
			printf("%f\n", vec_len(vec_mul(vec_norm(vec1), vec2)));
		return(vec_len(vec_mul(vec_norm(vec1), vec2)));
	}
}

double	len_mobius(t_vec point, t_mobius *mobius)
{
	double len;
	t_vec p;
	t_vec p2;
	t_vec vec;
	double a;
	t_segment segment;

	len = len_plane(point, &(mobius->plane));
	p = vec_sum(point, vec_dotdec(vec_dotdec(mobius->plane.norm, -1), len));
	p2 = vec_sum(point, vec_dotdec(mobius->plane.norm, len));
	vec = vec_sub(mobius->plane.point, p);
	if (vec_sqrdist(vec_sub(mobius->plane.point, p)) < vec_sqrdist(vec_sub(mobius->plane.point, p2)))
		vec = vec_sub(mobius->plane.point, p);
	else
	{
		vec = vec_sub(mobius->plane.point, p2);
		p = p2;
	}
	p = vec_sum(p, vec_dotdec(vec_norm(vec), vec_len(vec) - mobius->R));
	vec = vec_norm(vec_sub(mobius->plane.point, p));
	a = vec_dotvec(vec, mobius->vec);
	a = cos(acos(a) / 2);
	vec = rot(a, vec_mul(vec, mobius->norm), mobius->norm);
	segment.a = vec_sum(p, vec_dotdec(vec_norm(vec), 10));
	segment.b = vec_sum(p, vec_dotdec(vec_norm(vec), -10));
	return (len_segment(segment, point));
}


