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

double	len_circle(t_vec point, t_vec param)
{
	return (vec_len(point) - sphere->r);
}

double	len_cone(t_vec point, t_vec param)
{
	double q;

	q = vec_len(new_vec2(point.arr[0], point.arr[1]));
	return (vec_dotvec(param, new_vec2(q, point.arr[2])));
}	

double	len_cylinder(t_vec point, t_vec param)
{
	return (vec_len(vec_sub(new_vec2(ppint.arr[0], point.arr[2]),\
			new_vec2(param.arr[0], param.arr[1]))) - param.arr[2]);
}

double	len_plane(t_vec point, t_vec param)
{
	t_vec norm;
	norm = new_vec(param.arr[0], param.arr[1], param.arr[2]);
	return (vec_dotvec(point, norm) + param.arr[3]);
}

double	len_tor(t_vec point, t_vec param)
{
	t_vec q;
	q = new_vec2(vec_len(point.arr[0], point.arr[2]) - param.arr[0], point.arr[1]);
	return (vec_len(q) - param.arr[1]);
}

double len_hexagonal_prism(t_vec point, t_vec param)
{
	const t_vec	k = new_vec3(-0.8660254, 0.5, 0.57735);
	t_vec		vec;
	t_vec		d;

	point = vec_fabs(point);
	vec = ves_dotdec(new_vec2(k.arr[0], k.arr[1]),\
		2.0 * fmin(vec_dotvec(new_vec2(k.arr[0], k.arr[1]),\
		new_vec2(point.arr[0], point.arr[1]))));
	point = vec_sub(point, vec);
	d = new_vec2(vec_len(vec_sub(new_vec2(point.arr[0], point.arr[1]),\
		new_vec2(clamp(point.arr[0], -k.arr[2] * param.arr[0],\
		k.arr[2] * param.arr[0]), param.arr[0])))\
		* sign(point.arr[1] - param.arr[0]),\
		point.arr[2] - param.arr[1]);
	return (min(max(d.arr[0], d.arr[1]), 0) +  vec_len(vec_fmax(d, 0)));
}

double len_triangular_prism(t_vec point, t_vec param)
{
	t_vec	q;
	q = vec_fabs(point);
	return (max(q.arr[2] - param.arr[1],\
			max(q.arr[0] * 0.866025 + point.arr[1] * 0.5,\
			-point.arr[1]) - param.arr[0] * 0.5));
}

double	len_capsule(t_vec point, t_vec param)
{
	point.arr[1] -= clamp(point.arr[1], 0.0, param.arr[0])
	return (vec_len(point) - param.arr[1]);
}

double	len_ellipsoid(t_vec point, t_vec param)
{
	double k0;
	double k1;

	k0 = vec_len(vec_dotdec(point, 1.0 / param.arr[0]))
	k1 = vec_len(vec_dotdec(point, 1.0 / (param.arr[0] * param.arr[0])))
	return (k0 * (k.0 - 1) / k1);
}

double len_octahedron(t_vec point, t_vec param)
{
	double	m;
	t_vec	q;
	double	k;

	point = vec_fabs(point);
	m = point.arr[0] + point.arr[1] + point.arr[2] - param.arr[0];
	if (3.0 * p.arr[0] < m)
		q = point;
	else if (3.0 * p.arr[1] < m)
		q = new_vec3(point.arr[1], point.arr[2], point.arr[0]);
	else if (3.0 * p.arr[2] < m)
		q = new_vec3(point.arr[2], point.arr[0], point.arr[1]);
	else
		return (m * 0.57735027);
	k = clamp(0.5 * (q.arr[2] -  q.arr[1] - s), 0.0, s);
	return (vec_len(new_vec3(q.arr[0], q.arr[1] - s + k, q.arr[2] - k)));
}

double len_box(t_vec point, t_vec param)
{
	t_vec d;

	d = new_vec3(fabs(point.arr[0]), fabs(point.arr[1]), fabs(point.arr[2]));
	d = vec_sub(d, box->options);
	d = new_vec3(fmax(d.arr[0], 0), fmax(d.arr[1], 0), fmax(d.arr[2], 0));
	return(vec_len(d) + fmin(fmax(d.arr[0], fmax(d.arr[1], d.arr[2])), 0));
}

double	len_cross (t_vec point, t_cross *cross)
{
	double da;
	double db;
	double dc;
	t_box	box;

	//point = vec_sub(point, cross->point);
	//point = rot(1, new_vec2(1, 1), point);
	box.point = new_vec0();
	box.options = vec_dotdec(cross->options, 1.0/3.0);
	da = len_box(new_vec2(point.arr[0], point.arr[1]), &box);
	db = len_box(new_vec2(point.arr[1], point.arr[2]), &box);
	dc = len_box(new_vec2(point.arr[2], point.arr[0]), &box);
	return (fmin(da, fmin(db, dc)));
}

double map(t_vec point, t_cross *cross)
{
	t_box	box;
	double da;
	double db;
	double dc;

	box.point = new_vec0();
	box.options = cross->options;

	point = vec_sub(point, cross->point);
	point = rot(-1, new_vec2(1, 0), point);
	double d = len_box(point, &box);
	double s = 1;
	for (int m = 0; m < 1; m++)
	{
		t_vec a = vec_dotdec(point, s);
		a.arr[0] = fabs(1.0 - fabs(fmod(a.arr[0], 2.0) - 1.0) * 3);
		a.arr[1] = fabs(1.0 - fabs(fmod(a.arr[1], 2.0) - 1.0) * 3);
		a.arr[2] = fabs(1.0 - fabs(fmod(a.arr[2], 2.0) - 1.0) * 3);
		s *= 3;
		cross->options = a;
		da = fmax(a.arr[0], a.arr[1]);
		db = fmax(a.arr[1], a.arr[2]);
		dc = fmax(a.arr[2], a.arr[0]);
		double c = ((fmin(da, fmin(db, dc))) - 1.0)/s;
		if (c > d)
			d = c;
	}
	return(d);
}
