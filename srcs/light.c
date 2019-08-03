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

t_vec           get_uv_spehere(t_vec point)
{
    double v;
    double u;
    double phi;
    double theta;

    point = vec_norm(point);
    phi   = acos(-point.arr[2]);
    theta = acos(point.arr[1] / sin(phi)) / (2.0 * 3.14);
    if (point.arr[0] > 0)
        u = theta;
    else
        u = (1 - theta);
    if (sin(phi) == 0)
        u = 1;
    v = (1.0 - phi / 3.14);
    return (new_vec2(u, v));
}

t_vec           get_pixel(t_vec uv, t_texture texture)
{
    double v;
    double u;

    u = (int)(uv.arr[0] * texture.h) * texture.w * 3;
    v = (int)(uv.arr[1] * texture.w) * 3;
    return (new_vec3(texture.texture[(int)v + (int)u + 2],
                    texture.texture[(int)v + (int)u + 1],
                    texture.texture[(int)v + (int)u]));
}

t_vec           get_uv_cylinder(t_texture texture, t_vec point, double param)
{
    double v;
    double u;
    
    point.arr[2] = point.arr[2] / param;
    point.arr[0] = point.arr[0] / param;

    v = cos(point.arr[2]);
    if (point.arr[0] < 0)
        v = fabs(v - 1);
    if (point.arr[2] < 0)
        v = fabs(v - 1);
    u = fmod(point.arr[1] / texture.len_u, 1);
    if (u < 0)
        u += 1;
    v *= 2;
    return (new_vec2(u, v));
}

t_vec           get_uv_cone(t_texture texture, t_vec point)
{
    double v;
    double u;
    double z;
    
    z = point.arr[2];
    point.arr[2] = 0;
    point = vec_norm(point);

    v = cos(point.arr[1]) * 2;
    u = fmod(fabs(z / texture.len_u), 1);
    return (new_vec2(u, v));
}

t_vec           get_uv_plane(t_texture texture, t_vec point)
{
    double v;
    double u;

    v = fmod(point.arr[0] / texture.len_v, 1);
    u = fmod(point.arr[1] / texture.len_u, 1);
    if (u < 0)
        u += 1;
    if (v < 0)
        v += 1;
    return (new_vec2(u, v));
}

t_vec           get_color_obj(t_point_data shadow)
{
    t_vec point;
    
    point = rot(shadow.obj->rot_quat, vec_sub(shadow.point, shadow.obj->point));
    if (shadow.obj->texture.texture)
    {
        if (shadow.obj->type == SPHERE)
            return (get_pixel(get_uv_spehere(point), shadow.obj->texture));
        if (shadow.obj->type == CYLINDER)
            return (get_pixel(get_uv_cylinder(shadow.obj->texture, point, shadow.obj->param.arr[2]), shadow.obj->texture));
        if (shadow.obj->type == CONE)
            return (get_pixel(get_uv_cone(shadow.obj->texture, point), shadow.obj->texture));
        if (shadow.obj->type == PLANE)
            return (get_pixel(get_uv_plane(shadow.obj->texture, point), shadow.obj->texture));
    }
    return (shadow.obj->color);
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

int     get_shadow(t_scene objs, t_vec vec,
							t_accuracy accuracy, t_point_data point_data)
{
    t_vec point;
    t_point_data shadow;

    return (0);
    point = point_data.point;

    if (point_data.obj->amplitude)
        objs.ignore = point_data.obj;
    shadow = shadowmarching(objs, vec, accuracy, point);
    if (shadow.obj)
        return (1);
    else
        return (0);
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
            return (new_vec0());
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
                objs.lights[objs.number_lights].r), point_data->point);
            accuracy.max_dist = vec_len(li);
            if (!get_shadow(objs, vec_norm(li), accuracy, *point_data))
            {
                n_dot_l = vec_dotvec(point_data->norm, vec_norm(li));
                if (n_dot_l > 0)
                    i += objs.lights[objs.number_lights].intensity * (n_dot_l) / (vec_len(li));
                if (point_data->obj->specular > 0)
                {
                    hw_vec = vec_norm(vec_sum(vec_dotdec(li, 1), vec_norm(vec_dotdec(vec, -1))));
                    n_dot_l = vec_dotvec(hw_vec, point_data->norm);
                    n_dot_l = vec_dotvec(get_ref_vec(*point_data, vec_dotdec(li, -1)), vec_norm(vec_dotdec(vec, -1)));
                    if (n_dot_l > 0)
                        i += objs.lights[objs.number_lights].intensity * pow(n_dot_l, point_data->obj->specular) / (vec_len(li));
                }
            }
        }
    }
    return(vec_dotdec(point_data->color, i));
}
