//#include "srcs/vector.c"
# include "incs/objects_cl.h"


//#include "incs/objects.h"
//#include "srcs/vec_sum.c"
//#include "srcs/len_obj.c"
//#include "srcs/vec_mul.c"
//#include "srcs/vec_math.c"

t_vec			rand_point(t_vec point, double r)
{
	t_vec	v;

	v = (double4)(1.0, 2.0, 3.0, 4.0);
	//v.arr[0] = (rand() % 1024) * (rand() % 2 - 0.5);
	//v.arr[1] = (rand() % 1024) * (rand() % 2 - 0.5);
	//v.arr[2] = (rand() % 1024) * (rand() % 2 - 0.5);
	v = normalize(v);
	v = v * r;
	point += v;
	return (point);
}

t_point_data	crate_point_data(t_vec norm,
								 __global t_obj *obj, t_vec point, t_vec color)
{
	t_point_data point_data;

	point_data.norm = norm;
	point_data.obj = obj;
	point_data.point = point;
	point_data.color = color;
	return (point_data);
}

t_vec			rot(t_quat quat, t_vec v)
{
	t_quat t;

	t = quat * v;
	t = t * (double4)(-quat.xyz, quat.w);
	return ((double4)(t.x, t.y, t.z, 0.0));
}

double			ft_len(t_obj obj, t_vec point)
{
	if (obj.type == SPHERE)
		return distance(obj.point, point);
	else
		return distance(obj.point, point);
}

double			update_r(t_obj new_obj, t_vec point)
{
	double len;

	point = point - new_obj.point;
	point = rot(new_obj.rot_quat, point);
	if (new_obj.fract > 0)
	{
		point = fmod(point.arr[0], new_obj.fract) - new_obj.fract * 0.5;
	}
	len = ft_len(new_obj, point) - new_obj.rad;
	return (len);
}

double			get_dist(int neg,
		__global t_obj **obj,
		t_vec point,
		t_scene scene)
{
	int		counter;
	double	r;
	double	dist;

	counter = 0;
	dist = scene.accuracy->max_dist + 1;
	while (counter != scene.number_objs)
	{
		if (neg == scene.objs[counter].neg
		&& (!scene.ignore || scene.objs[counter].ind != scene.ignore->ind))
		{
			r = update_r(scene.objs[counter], point);
			if (r < dist)
			{
				//dist = opSmoothUnion(dist, r, 0.1);
				dist = r;
				*obj = scene.objs + counter;
			}
		}
		counter++;
	}
	return (dist);
}

t_vec			get_normal(t_vec point, t_obj obj)
{
	double e = 0.0053;
	t_vec		vec;

	vec = (double4)((update_r(obj, (point + (double4)(e, 0.0, 0.0, 0.0)))
			- update_r(obj, (point - (double4)(e, 0.0, 0.0, 0.0)))),
		   (update_r(obj, (point + (double4)(0.0, e, 0.0, 0.0)))
			- update_r(obj, (point - (double4)(0.0, e, 0.0, 0.0)))),
		   (update_r(obj, (point + (double4)(0.0, 0.0, e, 0.0)))
			- update_r(obj, (point - (double4)(0.0, 0.0, e, 0.0)))), 0.0);
	//vec = 0;
	if (obj.neg)
		vec = vec * -1;
	return (normalize(vec));
}

t_point_data	raymarching(t_scene scene,
		double4 vec,
		t_vec point)
{
	double	r[2];
	__global t_obj	*obj;
	__global t_obj	*obj2;
	double	dist;
	t_vec	new_point;

	dist = 0;
	obj = 0;
	new_point = point;
	if (scene.accuracy->depth_march-- &&
		   dist < scene.accuracy->max_dist)
	{
		r[0] = get_dist(0, &obj, new_point, scene);
		if (r[0] < 0)
			r[0] = fabs(fmin(r[0], scene.accuracy->delta * -1.1));
		r[1] = get_dist(1, &obj2, new_point, scene);
		r[0] = fmax(r[0], -r[1]);
		if (r[0] != -r[1])
			obj2 = obj;
		if (r[0] < scene.accuracy->delta)
		{

			return (crate_point_data(
					get_normal(new_point, *obj2),
					obj,
					new_point,
					obj->color)
			);
		}
		dist += r[0];
		new_point = (vec * dist) + point;
	}
	return (crate_point_data(
			(double4)(0.0, 0.0, 0.0, 0.0),
			0,
			(double4)(0.0, 0.0, 0.0, 0.0),
			(double4)(0.0, 0.0, 0.0, 0.0)));
}


////////////////////////////////////////////////////////////////////////////////

/*


t_point_data	ray_render(t_scene scene, t_vec point, t_accuracy accuracy)
{
	int				depth_ref;
	t_point_data	point_data;
	t_point_data	*points;

	point_data = raymarching(scene, point, accuracy, scene.cam);
	return (point_data);
}

t_point_data get_point(t_scene objs, t_vec vec,
					   t_accuracy accuracy)
{
	t_point_data point_data;
	t_point_data shadow;

	point_data = ray_render(objs, vec, accuracy, raymarching);
	shadow = point_data;
	if(shadow.obj)
		shadow.color = shadow.obj->color;
	while (1)
	{
		if (shadow.obj && shadow.obj->refraction)
			vec = transparency(vec, shadow);
		else
			break;
		shadow = raymarch_in_obj(shadow.obj, vec, accuracy, shadow.point);
		if(!shadow.obj)
			break;
		vec = transparency(vec, shadow);
		objs.ignore = shadow.obj;
		shadow = ray_render(objs, vec, accuracy, raymarching);
	}
	if(shadow.obj)
		shadow.color = get_color_obj(shadow);
	return(shadow);
}


t_vec   lightt(t_scene objs, t_vec vec,
			   t_accuracy accuracy, t_point_data *point_data)
{
	double i;
	double n_dot_l;
	t_vec li;
	t_vec hw_vec;

	if (accuracy.depth_pt == 1)
		*point_data = get_point(objs, vec, accuracy);
	if (!point_data->obj)
		return ({0.0, 0.0, 0.0, 0.0});
	i = 0.0;
	while (objs.number_lights--)
	{
		if (objs.lights[objs.number_lights].type == AMBIENT)
			i += objs.lights[objs.number_lights].intensity;
		else
		{

			if (objs.lights[objs.number_lights].type == DIRECT)
				li = objs.lights[objs.number_lights].vec;
			else
				li = (rand_point(
						objs.lights[objs.number_lights].point,
						objs.lights[objs.number_lights].r)
					- point_data->point);
			accuracy.max_dist = vec_len(li);
			if (!get_shadow(objs, normalize(li), accuracy, *point_data))
			{
				n_dot_l = vec_dotvec(point_data->norm, normalize(li));
				if (n_dot_l > 0)
					i += objs.lights[objs.number_lights].intensity * (n_dot_l) / (vec_len(li));
				hw_vec = normalize(vec_sum(vec_dotdec(li, 1), normalize(vec_dotdec(vec, -1))));
				n_dot_l = vec_dotvec(hw_vec, point_data->norm);
				n_dot_l = vec_dotvec(get_ref_vec(*point_data, vec_dotdec(li, -1)), normalize(vec_dotdec(vec, -1)));
				if (n_dot_l > 0)
					i += objs.lights[objs.number_lights].intensity * pow(n_dot_l, 128) / (vec_len(li));
			}
		}
	}
	return(vec_dotdec(point_data->color, i));
}
t_vec	antialiasing(t_scene *scene, double x, double y, t_accuracy accuracy, t_point_data *point_data)
{
	double	d_x;
	double	d_y;
	t_vec	color_1;
	t_vec	color_2;

	color_1 = {0.0, 0.0, 0.0, 0.0};
	color_2 = {0.0, 0.0, 0.0, 0.0};
	d_x = 0;
	scene.ignore = 0;
	while (x + d_x < x + 1.0 / scene.w)
	{
		d_y = 0;
		while (y + d_y < y + 1.0 / scene.h)
		{
			color_1 = color_1 + lightt(scene,
					normalize({((x + d_x), (y + d_y), scene.FOW / 2)), 0.0}),
					accuracy, point_data);
			d_y += 1.0 / accuracy.rpp / scene.h;
		}
		color_1 = color_1 / accuracy.rpp;
		color_2 = color_1 + color_2;
		d_x += 1.0 / accuracy.rpp / scene.w;
	}
	return (color_2 / accuracy.rpp);
}


t_obj	*get_objects(__global t_obj *objects, int count)
{
	t_obj	objs[count];
	int		i;

	i = 0;
	while (i < count)
	{
		objs[i].type = objects[i].type;
		objs[i].rot_quat = objects[i].rot_quat;
		objs[i].point = objects[i].point;
		objs[i].color = objects[i].color;
		objs[i].param = objects[i].param;
		objs[i].rad = objects[i].rad;
		objs[i].ind = objects[i].ind;
		objs[i].reflection = objects[i].reflection;
		objs[i].refraction = objects[i].refraction;
		objs[i].neg = objects[i].neg;
		objs[i].fract = objects[i].fract;
		++i;
	}
	return (objs);
}

*/


__kernel void	ray_tracing(__global int *obj_count,
							 __global int *light_count,
							 __global int *width,
							 __global int *height,
							 __global t_vec *cam,
							 __global t_light *lights,
							__global t_obj *obj,
                            __global t_obj *ignore,
							__global t_point_data *points_data,
							__global t_vec *scene_color,
							__global t_accuracy *accuracy,
							__global int *pixels)
{
	int			x;
	int			y;
	t_vec		color;
	t_scene     scene;
	int			i = get_global_id(0);

	//printf("%lf, %lf, %lf,\n",
	//	cam->x,
	//	cam->y,
	//	cam->z);
	scene.w = *width;
	scene.h = *height;
	scene.number_objs = *obj_count;
	scene.number_lights = *light_count;
	scene.cam = *cam;
	x = i % (scene.w);
	y = i / (scene.w);
	scene.lights = lights;
	//printf("%d\n", *obj_count);
	scene.objs = obj;
	scene.ignore = ignore;
	//scene.objs[0] = obj[0];
	//scene.objs[0].type = obj[0].type;
	scene.color = scene_color;
	scene.points_data = points_data;
	scene.accuracy = accuracy;
	//color = antialiasing(&scene,
	//					 ((double)x / scene.w) - 0.5,
	//					 ((double)y / scene.h) - 0.5,
	//					scene.accuracy,
	//					scene.points_data + x + scene.w * y);
	t_vec point = (double4)((x - (scene.w) * 0.5) / (scene.w),
							(y - (scene.h) * 0.5) / (scene.h),
							10.5, 1);
	t_point_data rm = raymarching(scene, point, *cam);
	if (rm.obj)
	{
		color = rm.obj->color;
		if (i == 500*1204 + 500)
			printf("yeah!\n");
	}
	else
	{
		if (i == 500*1204 + 500)
			printf("nooo!\n");
		color = (double4)(0.0, 0.0, 0.0, 0.0);
	}
	if (i == 500*1204 + 500)
		printf("%lf, %lf, %lf, %lf\n",
				scene.objs[1].color.x,
				scene.objs[1].color.y,
				scene.objs[1].color.z,
				scene.objs[1].color.w);
	color = fmin(color, (double)255.0);
	if (accuracy->depth_pt == 1)
		scene_color[x + (scene.w) * y] = color;
	else
		scene_color[x + (scene.w) * y] = scene_color[x + (scene.w) * y] + color;
	color = scene_color[x + (scene.w) * y] / accuracy->depth_pt;
	pixels[x + (scene.w) * y] =
			(int)(color.x) << 16 |
			(int)(color.y) << 8 | (int)(color.z) | 0xff << 24;
}
