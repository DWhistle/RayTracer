#include "ray_render.h"

double	len_circle(t_vec point, t_sphere *sphere)
{
	return (vec_len(vec_sub(point, sphere->point)) - sphere->r);
}

double	len_cone(t_vec point, t_cone *cone)
{
	double f;

	point = vec_sub(point, cone->point);
	point = rot(-0.5, new_vec2(1, 1), point);
	f = vec_len(new_vec2(point.arr[0], point.arr[1]));
	return (vec_dotvec(new_vec2(0.7, 0.1), new_vec2(f, point.arr[2])));

}	

double	len_cylinder(t_vec point, t_cylinder *cylinder)
{
	t_vec	vec;

	point = vec_sub(point, cylinder->point);
	point = rot(1, new_vec2(1, 0), point);
	vec = new_vec2(point.arr[0], point.arr[2]);
	vec = new_vec2(fabs(vec_len(vec)), fabs(point.arr[1]));
	vec = vec_sub(vec, new_vec2(cylinder->r, 100));
	double k = fmin(fmax(vec.arr[0], vec.arr[1]),0.0);
	vec.arr[0] = fmax(vec.arr[0], 0.0);
	vec.arr[1] = fmax(vec.arr[1], 0.0);
	return (k + vec_len(vec));
}

double	len_plane(t_vec point, t_plane *plane)
{
	return (fabs(vec_dotvec(point, plane->norm) - vec_dotvec(plane->point, plane->norm)));
}

double	len_tor(t_vec point, t_tor *tor)
{
	t_vec vec;

	point = vec_sub(point, tor->plane.point);
	point = rot(1, new_vec2(1, 0), point);
	vec = new_vec2(vec_len(new_vec2(point.arr[0], point.arr[2])) - tor->R, point.arr[1]);
	return (vec_len(vec) - tor->r);
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


