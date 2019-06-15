#include "ray_render.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <quat.h>

t_vec			rot(double angle, t_vec u, t_vec v)
{

	t_quat quat;
	t_quat t;

	quat = create_quat(u, angle);
	t = quat_mul_vector(quat, v);
	t = quat_mul_quat(t, quat_invert(quat));
	return (new_vec3(t.x, t.y, t.z));
}

t_vec			rand_vec(t_vec vec)
{
	t_vec	v;

	v = new_vec3(0, 0, 0);
	v.arr[0] = (rand() % 1000) * (rand() % 2 - 0.5) * 2;
	v.arr[1] = (rand() % 100);
	v.arr[2] = (rand() % 1000) * (rand() % 2 - 0.5) * 2;
	v = vec_norm(v);
	v = rot(vec_dotvec(new_vec3(0, 1, 0), vec), vec_mul(new_vec3(0, 1, 0), vec), v);
	
	return (vec_norm(v));
}

int				is_light(t_scene scene, int ind)
{
	int counter;

	counter = 0;
	while (counter != scene.number_lights)
	{
		if (scene.lights[counter].ind == ind)
			return (1);
		counter++;
	}
	return (0);
}

t_point_data	path_tracing(t_scene scene, t_vec vec,
							t_accuracy accuracy, t_vec point)
{
	t_point_data	point_data;
	t_point_data	point_data2;
	int				depth_pt;
	t_vec			norm;
	int				i;
	int				p = 500;
	double			k;

	point_data = raymarching(scene, vec, accuracy, point);
	i = 0;
	k = 0;
	while (i++ < p)
	{
		point_data2 = point_data;
		depth_pt = 0;
		while (accuracy.depth_pt > depth_pt++ && point_data2.obj)
		{
			scene.ignore = point_data2.obj;
			norm = point_data2.norm;
			if (point_data2.obj && is_light(scene, point_data2.obj->ind))
			{
				scene.ignore = 0;
				k += 1.0 / (depth_pt/ 2);
				break ;
			}
			point_data2 = raymarching(scene, rand_vec(norm), accuracy, point);
		}	
	}
	point_data.color = vec_dotdec(point_data.obj->color, k / p * 2);
	return (point_data);
}
