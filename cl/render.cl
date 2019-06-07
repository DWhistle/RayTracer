#include "srcs/vector.c"
#include "incs/objects1.h"
#include "srcs/vec_sum.c"
#include "incs/vector.h"

double	len_circle(t_vec point, __global t_obj2 *sphere);
double	len_cone(t_vec point, __global t_obj2 *cone);
double	len_cylinder(t_vec point, __global t_obj2 *cylinder);
double	len_plane(t_vec point, __global t_obj2 *plane);
double			update_r(double r, __global t_obj2 *new_obj, t_vec point, __global t_scene *objs);
t_vec			get_normal(t_vec point, __global t_obj2 *obj);
t_point_data	crate_point_data(t_vec norm,
				__global t_obj2 *obj, t_vec point, t_vec color);
t_point_data	raymarching(__global t_scene *objs, t_vec vec,
				__global t_accuracy *accuracy, t_vec point, __global t_obj2 *obj);
t_vec			rand_vec(t_vec vec);
int				is_light(__global t_scene *scene, int ind);
t_point_data	path_tracing(__global t_scene *scene, t_vec vec,
__global t_accuracy *accuracy, t_vec point, __global  t_obj2 *objs);
t_vec	get_ref_vec(t_point_data point_data, t_vec vec);
t_vec	get_ref_color(t_point_data *points);
t_vec	f(t_point_data *points, int depth_ref, __global t_scene *scene);
t_vec	ray_render(__global t_scene *scene, t_vec point, __global t_accuracy *accuracy, __global  t_obj2 *objs);
t_vec	antialiasing(__global t_scene *scene, double x, double y, __global t_accuracy *accuracy, __global t_obj2 *objs);
int		rand (void);

int rand (void)
{
	uint next = 1;
	next  = ParallelRNG(get_global_id(0), get_global_id(1));
	return (next);
}

double		vec_dotvec(t_vec4 v1, t_vec4 v2)
{
	return (v1.vec.x * v2.vec.x + v1.vec.y * v2.vec.y + v1.vec.z * v2.vec.z + v1.vec.w * v2.vec.w);
}

t_vec4		vec_dotdec(t_vec4 v1, double val)
{
	t_vec4	ret;

	ret.vec.x = v1.vec.x * val;
	ret.vec.y = v1.vec.y * val;
	ret.vec.z = v1.vec.z * val;
	ret.vec.w = v1.vec.w * val;
	return (ret);
}

t_vec4		vec_mul(t_vec4 v1, t_vec4 v2)
{
	t_vec4	ret;

	ret.vec.x = v1.vec.y * v2.vec.z - v1.vec.z * v2.vec.y;
	ret.vec.y = v1.vec.z * v2.vec.x - v1.vec.x * v2.vec.z;
	ret.vec.z = v1.vec.x * v2.vec.y - v1.vec.y * v2.vec.x;
	ret.vec.w = 1;
	return (ret);
}

double	vec_sqrdist(t_vec4 vec)
{	
	return (vec.vec.x * vec.vec.x +
			vec.vec.y * vec.vec.y +
			vec.vec.z * vec.vec.z +
			vec.vec.w * vec.vec.w);
}

double vec_len(t_vec4 vec)
{
	double sqr;
	sqr = sqrt(vec_sqrdist(vec));
	return (sqr);
}

t_vec4		vec_norm(t_vec4 v)
{
	t_vec4		vec;
	double	dist;

	dist = 1.0 / sqrt(vec_sqrdist(v));
	vec.vec.x = v.vec.x * dist;
	vec.vec.y = v.vec.y * dist;
	vec.vec.z = v.vec.z * dist;
	vec.vec.w = v.vec.w * dist;
	return (vec);
}

double	len_circle(t_vec point,  __global t_obj2 *sphere)
{
	double	len;
	t_vec	vec;

	vec = sphere->point;
	len = vec_len(vec_sub(point, vec)) - sphere->r;
	return (len);
}

double	len_cylinder(t_vec point,  __global t_obj2 *cylinder)
{
	double	k;
	t_vec	vec;
	t_vec	vec1;

	vec = cylinder->point;
	vec = vec_sub(point, vec);
	vec1 = cylinder->vec;
	k = vec_dotvec(vec, vec1);
	k = vec_len(vec_sub(vec, vec_dotdec(vec1, k))) - cylinder->r;
	return (k);
}

double	len_plane(t_vec point, __global t_obj2 *plane)
{
	return (fabs(plane->vec.arr[0] * point.arr[0] + \
			plane->vec.arr[1] * point.arr[1] + \
			plane->vec.arr[2] * point.arr[2] - \
			plane->vec.arr[0] * plane->point.arr[0] - \
			plane->vec.arr[1] * plane->point.arr[1] - \
			plane->vec.arr[2] * plane->point.arr[2]));
}

double			update_r(double r, __global t_obj2 *new_obj, t_vec point, __global t_scene *objs)
{
	double len;

	len = 0;
	if (objs->ignore && objs->ignore->ind == new_obj->ind)
		return (r);
	if (new_obj->type == SPHERE)
		len = len_circle(point, new_obj);
	else if (new_obj->type == PLANE)
		len = len_plane(point, new_obj);
	else if (new_obj->type == CYLINDER)
		len = len_cylinder(point, new_obj);
	if (r == -1 || len < r)
		r = len;
	return (r);
}

t_vec			get_normal(t_vec point, __global t_obj2 *obj)
{
	double		k;
	t_vec		vec;
	t_vec		vec1;

	if (obj->type == SPHERE)
	{
		vec = (obj)->point;
		vec = vec_norm(vec_sub(point, vec));
		return (vec);
	}
	else if (obj->type == PLANE)
	{
		vec = (obj)->vec;
		return (vec);
	}
	else if (obj->type == CYLINDER)
	{
		vec1 = obj->point;
		vec = vec_sub(point, vec1);
		vec1 = obj->vec;
		k = vec_dotvec(vec, vec1);
		vec = vec_norm(vec_sub(vec, vec_dotdec(vec1, k)));
		return (vec);
	}
	vec = new_vec0();
	return (vec);
}

t_point_data	crate_point_data(t_vec norm,
				__global t_obj2 *obj, t_vec point, t_vec color)
{
	t_point_data point_data;

	point_data.norm = norm;
	point_data.obj = obj;
	point_data.point = point;
	point_data.color = color;
	return (point_data);
}

t_point_data	raymarching(__global t_scene *objs, t_vec vec,
							__global t_accuracy *accuracy, t_vec point, __global  t_obj2 *obj)
{
	double	r;
	int		counter;
	double	depth_march;
	t_vec	next_point;
	t_vec	color;
	t_point_data p;

	next_point = point;
	depth_march = accuracy->depth_march;
	while (depth_march-- &&
			vec_len(vec_sub(point, next_point)) < accuracy->max_dist)
	{
		r = -1;
		counter = objs->number_objs;
		while (counter--)
		{
			r = update_r(r, obj + counter, next_point, objs);
			if (r < accuracy->delta && r != -1)
			{
				p = crate_point_data(get_normal(next_point,
			obj + counter), obj + counter, next_point, new_vec3(0, 0, 0));
				return (p);
			}
		}
		next_point = vec_sum(next_point, vec_dotdec(vec, r));
	}
	p = crate_point_data(new_vec0(), 0, new_vec0(), new_vec3(0, 0, 0));
	return (p);
}

t_vec			rand_vec(t_vec vec)
{
	if (vec.arr[0] == 0)
		vec.arr[0] = (rand() % 200000 + 1) * ((double)(rand() % 2) - 0.5);
	else
		vec.arr[0] = (rand() % 100000 + 1) * vec.arr[0];
	if (vec.arr[1] == 0)
		vec.arr[1] = (rand() % 200000 + 1) * ((double)(rand() % 2) - 0.5);
	else
		vec.arr[1] = (rand() % 100000 + 1) * vec.arr[1];
	if (vec.arr[2] == 0)
		vec.arr[2] = (rand() % 200000 + 1) * ((double)(rand() % 2) - 0.5);
	else
		vec.arr[2] = (rand() % 100000 + 1) * vec.arr[2];
	vec = vec_norm(vec);
	return (vec);
}

int				is_light(__global t_scene *scene, int ind)
{
	int counter;

	counter = 0;
	while (counter != scene->number_lights)
	{
		if (scene->lights[counter].ind == ind)
			return (1);
		counter++;
	}
	return (0);
}

t_point_data	path_tracing(__global t_scene *scene, t_vec vec,
							__global t_accuracy *accuracy, t_vec point, __global  t_obj2 *objs)
{
	t_point_data	point_data;
	t_point_data	point_data2;
	int				depth_pt;
	t_vec			norm;
	t_vec			vec1;

	depth_pt = 0;
	point_data = raymarching(scene, vec, accuracy, point, objs);
	point_data2 = point_data;
	point_data.color = point_data.obj->color;
	return (point_data);
	while (accuracy->depth_pt > depth_pt++ && point_data2.obj)
	{
		scene->ignore = point_data2.obj;
		norm = point_data2.norm;
		if (point_data2.obj && is_light(scene, point_data2.obj->ind))
		{
			scene->ignore = 0;
			point_data.color = point_data.obj->color;
			point_data.color = vec_dotdec(point_data.color, 1.0 / depth_pt);
			break ;
		}
		//vec1 = rand_vec(norm);
		point_data2 = raymarching(scene, get_ref_vec(point_data2, norm), accuracy, point, objs);
	}
	return (point_data);
}

t_vec	get_ref_vec(t_point_data point_data, t_vec vec)
{
	vec = vec_dotdec(vec, -1);
	vec = vec_sub(vec_dotdec(point_data.norm,
	vec_dotvec(point_data.norm, vec) * 2), vec);
	vec = vec_norm(vec);
	return (vec);
}

t_vec	get_ref_color(t_point_data *points)
{
	int		i;
	t_vec	color_ref;
	t_vec	color;
	double	ref;

	i = 0;
	while (points[i].obj)
		i++;
	while (i-- != 1)
	{
		color_ref = points[i].color;
		ref = points[i - 1].obj->reflection;
		color = points[i - 1].color;
		color = vec_sum(vec_dotdec(color, 1 - ref), vec_dotdec(color_ref, ref));
		points[i - 1].color = color;
	}
	return (points[0].color);
}

t_vec	f(t_point_data *points, int depth_ref, __global t_scene *scene)
{
	t_vec			color;

	points[depth_ref].obj = 0;
	color = get_ref_color(points);
	scene->ignore = 0;
	return (color);
}

t_vec	ray_render(__global t_scene *scene, t_vec point, __global t_accuracy *accuracy, __global  t_obj2 *objs)
{
	int				depth_ref;
	t_point_data	point_data;
	t_point_data	points[accuracy->depth_ref + 1];
	t_vec			vec;

	vec = scene->cam;
	point_data = path_tracing(scene, vec_norm(vec_sub(point, vec)), accuracy, vec, objs);
	if (point_data.obj)
	{
		points[0] = point_data;
		depth_ref = 0;
		while (accuracy->depth_ref > depth_ref++ &&
		point_data.obj && point_data.obj->reflection)
		{
			scene->ignore = point_data.obj;
			point_data = path_tracing(scene,
			get_ref_vec(point_data, vec), accuracy, point_data.point, objs);
			points[depth_ref] = point_data;
		}
		scene->ignore = 0;
		vec = f(points, depth_ref, scene);
		return (vec);
	}
	return (vec);
}

t_vec	antialiasing(__global t_scene *scene, double x, double y, __global t_accuracy *accuracy, __global t_obj2 *objs)
{
	double	d_x;
	double	d_y;
	t_vec	color_1;
	t_vec	color_2;
	t_vec	color_3;

	color_1 = new_vec0();
	color_2 = new_vec0();
	d_x = 0;
	scene->ignore = 0;
	while (x + d_x < x + 1)
	{
		d_y = 0;
		while (y + d_y < y + 1)
		{
			color_3 = ray_render(scene, new_vec3((x + d_x), (y + d_y), 400), accuracy, objs);
			color_1 = vec_sum(color_1, color_3);
			d_y += 1.0 / accuracy->rpp;
		}
		color_1 = vec_dotdec(color_1, 1.0 / accuracy->rpp);
		color_2 = vec_sum(color_1, color_2);
		d_x += 1.0 / accuracy->rpp;
	}
	color_2 = vec_dotdec(color_2, 1.0 / accuracy->rpp); 
	return (color_2);
}

__kernel void	ray_tracing(__global t_accuracy *accuracy,\
							__global t_scene *scene,\
							__global t_light *lights,\
							__global t_obj2 *obj,\
							__global int *pixels,\
							__global int *w,\
							__global int *h)
{
	int			x;
	int			y;
	t_vec		color;
	int			i = get_global_id(0);

	x = i % *w;
	y = i / (*h*2);

	scene->number_objs = 9;
	scene->lights = lights;
	color = antialiasing(scene, x - *w / 2, y - *h / 2, accuracy, obj);
	if (color.arr[0] > 255)
		color.arr[0] = 255;
	if (color.arr[1] > 255)
		color.arr[1] = 255;
	if (color.arr[2] > 255)
		color.arr[2] = 255;
	pixels[i] = (int)(color.arr[0]) * 256 * 256 + (int)(color.arr[1]) * 256 + (int)(color.arr[2]);
}
