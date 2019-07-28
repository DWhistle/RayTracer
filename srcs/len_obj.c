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

double	len_sphere(t_vec point, t_vec param)
{
	return (vec_len(point) - fabs(param.arr[0]));
}

double	len_cone(t_vec point, t_vec param)
{
	double q;

	q = vec_len(new_vec2(point.arr[0], point.arr[1]));
	return (vec_dotvec(param, new_vec2(q, point.arr[2])));
}	

double	len_cylinder(t_vec point, t_vec param)
{
	return (vec_len(vec_sub(new_vec2(point.arr[0], point.arr[2]),\
			new_vec2(param.arr[0], param.arr[1]))) - param.arr[2]);
}

double	len_plane(t_vec point, t_vec param)
{
	t_vec norm;
	norm = new_vec3(param.arr[0], param.arr[1], param.arr[2]);
	return (vec_dotvec(point, norm) + param.arr[3]);
}

double	len_tor(t_vec point, t_vec param)
{
	t_vec q;
	q = new_vec2(vec_len(new_vec2(point.arr[0], point.arr[2])) - param.arr[0], point.arr[1]);
	return (vec_len(q) - param.arr[1]);
}

double len_hexagonal_prism(t_vec point, t_vec param)
{
	const t_vec	k = new_vec3(-0.8660254, 0.5, 0.57735);
	t_vec		vec;
	t_vec		d;

	point = vec_fabs(point);
	vec = vec_dotdec(new_vec2(k.arr[0], k.arr[1]),\
		2.0 * fmin(vec_dotvec(new_vec2(k.arr[0], k.arr[1]),\
		new_vec2(point.arr[0], point.arr[1])), 0));
	point = vec_sub(point, vec);
	d = new_vec2(vec_len(vec_sub(new_vec2(point.arr[0], point.arr[1]),\
		new_vec2(clamp(point.arr[0], -k.arr[2] * param.arr[0],\
		k.arr[2] * param.arr[0]), param.arr[0])))\
		* point.arr[1] - param.arr[0] > 0 ? 1 : -1,\
		point.arr[2] - param.arr[1]);
	return (fmin(fmax(d.arr[0], d.arr[1]), 0) +  vec_len(vec_fmax(d, 0)));
}

double len_triangular_prism(t_vec point, t_vec param)
{
	t_vec	q;
	q = vec_fabs(point);
	return (fmax(q.arr[2] - param.arr[1],\
			fmax(q.arr[0] * 0.866025 + point.arr[1] * 0.5,\
			-point.arr[1]) - param.arr[0] * 0.5));
}

double	len_capsule(t_vec point, t_vec param)
{
	point.arr[1] -= clamp(point.arr[1], 0.0, param.arr[0]);
	return (vec_len(point) - param.arr[1]);
}

double	len_ellipsoid(t_vec point, t_vec param)
{
	double k0;
	double k1;

	k0 = vec_len(vec_dotdec(point, 1.0 / param.arr[0]));
	k1 = vec_len(vec_dotdec(point, 1.0 / (param.arr[0] * param.arr[0])));
	return (k0 * (k0 - 1) / k1);
}

double len_octahedron(t_vec point, t_vec param)
{
	double	m;
	t_vec	q;
	double	k;

	point = vec_fabs(point);
	m = point.arr[0] + point.arr[1] + point.arr[2] - param.arr[0];
	if (3.0 * point.arr[0] < m)
		q = point;
	else if (3.0 * point.arr[1] < m)
		q = new_vec3(point.arr[1], point.arr[2], point.arr[0]);
	else if (3.0 * point.arr[2] < m)
		q = new_vec3(point.arr[2], point.arr[0], point.arr[1]);
	else
		return (m * 0.57735027);
	k = clamp(0.5 * (q.arr[2] -  q.arr[1] - param.arr[0]), 0.0, param.arr[0]);
	return (vec_len(new_vec3(q.arr[0], q.arr[1] - param.arr[0] + k, q.arr[2] - k)));
}

double len_box(t_vec point, t_vec param)
{
	t_vec d;

	d = new_vec3(fabs(point.arr[0]), fabs(point.arr[1]), fabs(point.arr[2]));
	d = vec_sub(d, param);
	return(vec_len(vec_fmax(d, 0.0)) + fmin(fmax(d.arr[0], fmax(d.arr[1], d.arr[2])), 0));
}

float sdCross(t_vec p)
{
  float da = len_box(new_vec2(p.arr[0], p.arr[1]), new_vec2(1.0, 1.0));
  float db = len_box(new_vec2(p.arr[1], p.arr[2]), new_vec2(1.0, 1.0));
  float dc = len_box(new_vec2(p.arr[2], p.arr[0]), new_vec2(1.0, 1.0));
  //printf("da %f db %f dc %f", da, db, dc);
  return fmin(da,fmin(db,dc));
}

double map(t_vec point, t_vec param)
{
	double	d = len_box(point, param);
	double	c = sdCross(vec_dotdec(point, 1))/1.0;
	//printf ("d = %f\n", c);
	d = fmax(d, -c);
	return (d);
}

