#include "ray_render.h"

double clamp(double f, double s, double t)
{
	if (f < s)
		return (s);
	else if (f > t)
		return (t);
	else
		return (f);
}

t_vec vec_mult(t_vec f, t_vec s)
{
	return (new_vec4(
		f.arr[0] * s.arr[0],
		f.arr[1] * s.arr[1],
		f.arr[2] * s.arr[2],
		f.arr[3] * s.arr[3]
	));
}

double vec_len2(t_vec p)
{
	p = vec_mult(p, p);
	p = vec_mult(p, p);
	float a = p.arr[0]  + p.arr[1] + p.arr[2];
	return pow(a, 1.0/4.0);
}

double	len_circle(t_vec point, t_sphere *sphere)
{
	t_vec p = vec_sub(point, sphere->point);
	point.arr[0] = p.arr[1];
	point.arr[1] = p.arr[2];
	point.arr[2] = p.arr[0];
	return (vec_len(point) - sphere->r);
}

double	len_cone(t_vec point, t_cone *cone)
{
	t_vec	vec;
	t_vec	veck1;
	t_vec	veck2;
	t_vec	ca;
	t_vec	cb;
	double s;

	double f;

	point = vec_sub(point, cone->point);
	point = rot(1, new_vec2(1, 0), point);

	vec = new_vec2(vec_len(new_vec2(point.arr[0], point.arr[2])), point.arr[1]);
	veck1 = new_vec2(20, 10);
	veck2 = new_vec2(20 - 10, 2.0 * 10);
	ca = new_vec2(vec.arr[0] - fmin(vec.arr[0], (vec.arr[1] < 0) ? 10 : 20), fabs(vec.arr[1]) - 10);
	cb = vec_sub(vec, veck1);
	cb = vec_sum(cb, vec_dotdec(veck2, clamp(vec_dotvec(vec_sub(veck1, vec), veck2) / vec_sqrdist(veck2), 0.0, 1.0)));
	s = (cb.arr[0] < 0 && ca.arr[1] < 0) ? -1.0 : 1.0;
	return (s * sqrt(fmin(vec_sqrdist(ca), vec_sqrdist(cb))));

	
	f = vec_len(new_vec2(point.arr[0], point.arr[1]));
	return (vec_dotvec(vec_norm(new_vec2(0.7, 0.1)), new_vec2(f, point.arr[2])));
}	

float onion(float d, float h )
{
    return fabsf(d)-h;
}

double	len_cylinder(t_vec point, t_cylinder *cylinder)
{
	t_vec	vec;

	point = vec_sub(point, cylinder->point);
	point = rot(-1, new_vec2(1, 0), point);

	vec = new_vec2(point.arr[0], point.arr[2]);
	vec = new_vec2(vec_len(vec) - 2 * cylinder->r + 0, fabs(point.arr[1]) - 50);
	double k = fmin(fmax(vec.arr[0], vec.arr[1]),0.0);
	vec.arr[0] = fmax(vec.arr[0], 0.0);
	vec.arr[1] = fmax(vec.arr[1], 0.0);
	return (fabs(k + vec_len(vec)) - 2);
}

double	len_plane(t_vec point, t_plane *plane)
{
	point = vec_sub(point, plane->point);
	return (vec_dotvec(point, plane->norm));
}

double	len_tor(t_vec point, t_tor *tor)
{
	double k;

	point = vec_sub(point, tor->plane.point);
	point = rot(0, new_vec2(1, 0), point);
	point.arr[0] = fabs(point.arr[0]);
	k = (-1 * point.arr[0] > point.arr[1]) ? vec_dotvec(new_vec2(point.arr[0], point.arr[1]), new_vec2(-1, 1)) : vec_len(new_vec2(point.arr[0], point.arr[1]));
	return (sqrt(vec_dotvec(point, point) + tor->R * tor->R - 2 * tor->R * k) - tor->r);
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


