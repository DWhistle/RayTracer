#include "ray_render.h"

t_vec			rand_point(t_vec point, double r)
{
	t_vec	v;

	v = new_vec3(0, 0, 0);
	v.arr[0] = (rand() % 1024) * (rand() % 2 - 0.5);
	v.arr[1] = (rand() % 1024) * (rand() % 2 - 0.5);
	v.arr[2] = (rand() % 1024) * (rand() % 2 - 0.5);
	v = vec_norm(v);
    v = vec_dotdec(v, r);
	point = vec_sum(point, v);
	return (point);
}

t_point_data get_point(t_scene objs, t_vec vec,
							t_accuracy accuracy)
{
    t_point_data point_data;
    t_point_data shadow;

    point_data = ray_render(objs, vec, accuracy);
    shadow = point_data;
    while (1)
    {
        if (shadow.obj && shadow.obj->refraction)
            vec = transparency(vec, shadow);
        else
            break;
        objs.ignore = shadow.obj;
        shadow = ray_render(objs, vec, accuracy);
    }
    if(shadow.obj)
        point_data.color = shadow.obj->color;
    return(point_data);
}

int     get_shadow(t_scene objs, t_vec vec,
							t_accuracy accuracy, t_point_data point_data)
{
    t_vec point;
    t_point_data shadow;

    objs.ignore = point_data.obj;
    point = point_data.point;
    while (1)
    {
        shadow = raymarching(objs, vec, accuracy, point);
        if (shadow.obj && shadow.obj->refraction)
            vec = transparency(vec, shadow);
        else
            break;
        objs.ignore = shadow.obj;
    }
    if (shadow.obj)
        return (1);
    else
        return (0);
}

t_vec   lightt(t_scene objs, t_vec vec,
							t_accuracy accuracy)
{
    t_point_data point_data;
    double i;
    double n_dot_l;
    t_vec li;
    t_vec hw_vec;


    point_data = get_point(objs, vec, accuracy);
    if (!point_data.obj)
            return (new_vec0());
    //return (point_data.obj->color);
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
                li = vec_sub(rand_point(objs.lights[objs.number_lights].point,\
                objs.lights[objs.number_lights].r), point_data.point);
            accuracy.max_dist = vec_len(li);
            if (!get_shadow(objs, vec_norm(li), accuracy, point_data))
            {
                n_dot_l = vec_dotvec(point_data.norm, vec_norm(li));
                if (n_dot_l > 0)
                    i += objs.lights[objs.number_lights].intensity * (n_dot_l) / (vec_len(li));
                hw_vec = vec_norm(vec_sum(vec_dotdec(li, 1), vec_norm(vec_dotdec(vec, -1))));
                n_dot_l = vec_dotvec(hw_vec, point_data.norm);
                n_dot_l = vec_dotvec(get_ref_vec(point_data, vec_dotdec(li, -1)), vec_norm(vec_dotdec(vec, -1)));
                if (n_dot_l > 0)
                    i += objs.lights[objs.number_lights].intensity * pow(n_dot_l, 128) / (vec_len(li));
            }
        }
    }
    point_data.color = vec_dotdec(point_data.color, i);
    return (point_data.color);
}
