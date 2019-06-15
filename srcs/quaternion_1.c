#include "quat.h"

t_quat	quat_invert(t_quat q)
{
	t_quat res;

	res.w = q.w;
	res.x = -q.x;
	res.y = -q.y;
	res.z = -q.z;
	return (quat_scale(res, 1 / quat_length(res)));
}
