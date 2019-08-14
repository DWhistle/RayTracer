#include "ray_render.h"

t_vec	rot(t_quat quat, t_vec v)
{
	t_quat t;

	t = quat_mul_vector(quat, v);
	t = quat_mul_quat(t, quat_invert(quat));
	return (new_vec3(t.x, t.y, t.z));
}

t_vec	transparency(t_vec vec, t_point_data point)
{
	double	a;
	t_vec	v;

	a = acos(vec_dotvec(vec, point.norm));
	a = cos(asin(sin(a) * point.obj->refraction));
	v = rot(create_quat(vec_mul(vec, point.norm), a),\
			vec_dotdec(point.norm, -1));
	return (v);
}

t_point_data	get_transparency(t_scene *objs, t_vec vec, t_point_data point_data)
{
	t_point_data shadow;

	shadow = point_data;
	while (shadow.obj && shadow.obj->transparency)
	{
		objs->ignore = shadow.obj;
		shadow = ray_render(objs, vec, shadow.point, raymarching);
	}
	point_data.tranc_norm = shadow.norm;
	point_data.tranc_color = shadow.color;
	point_data.tranc_point = shadow.point;
	return (point_data);
}
