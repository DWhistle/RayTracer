#include "ray_render.h"
#include <quat.h>

t_vec			rot(double angle, t_vec u, t_vec v)
{
	t_quat quat;
	t_quat t;

    u = vec_norm(u);
	quat = create_quat(u, angle);
	t = quat_mul_vector(quat, v);
	t = quat_mul_quat(t, quat_invert(quat));
	return (new_vec3(t.x, t.y, t.z));
}

t_vec   transparency(t_vec vec, t_point_data point)
{
    double a;
    t_vec v;
    a = acos(vec_dotvec(vec, point.norm));
    a = cos(asin(sin(a) * point.obj->refraction));
    v = rot(a, vec_mul(vec, point.norm), vec_dotdec(point.norm, -1));
    return(v);
}
