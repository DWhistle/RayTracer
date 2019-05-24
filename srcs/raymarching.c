#include <math.h>
#include "ray_render.h"
#include "libft.h"
#include <stdio.h>
#include "SDL2/SDL.h"

double update_r(double r, t_obj new_obj, t_vec point)
{
    double len = 0;
    if (new_obj.type == CIRCLE)
        len = len_circle(point, new_obj.obj);
    else if (new_obj.type == PLANE)
        len = len_plane(point, new_obj.obj);
    else if (new_obj.type == CYLINDER)
        len = len_cylinder(point, new_obj.obj);
    else if (new_obj.type == CONE)
        len = len_cone(point, new_obj.obj);
    if(r == -1 || len < r)
        r = len;
    return (r);
}

double light_render(t_scene objs, t_point_data point_data, t_vec n)
{
    t_vec l;
    double dif;
    int counter = objs.number_lights;
    double i = 0;

    while (counter--)
    {
        if (objs.lights[counter].type == AMBIENT)
            i += objs.lights[counter].intensity;
        if (objs.lights[counter].type == POINT)
        {
            l = vec_sub(objs.lights[counter].point, point_data.point);
            l = vec_norm(l);
            dif = vec_dotvec(n, l);
            if (dif > 0)
                i += dif * objs.lights[counter].intensity;
        }
    }
    return (i);
}

t_vec get_normal(t_vec point, t_obj obj)
{
    t_cylinder *cylinder;
    double  k;
    t_vec   vec;

    if (obj.type == CIRCLE)
        return(vec_norm(vec_sub(point ,((t_sphere*)obj.obj)->point)));
    else if (obj.type == PLANE)
        return (((t_plane*)obj.obj)->norm);
    else if (obj.type == CYLINDER)
    {
        cylinder = (t_cylinder*)obj.obj;
        vec = vec_sub(point, cylinder->point);
        k = vec_dotvec(vec, cylinder->vec);
        return(vec_norm(vec_sub(vec, vec_dotdec(cylinder->vec, k))));
    }
    return (new_vec0());
}

t_point_data raymarching(t_scene objs, t_vec vec, t_accuracy accuracy, t_vec point)
{
    double r;
    int counter;
    t_point_data point_data;
    t_vec next_point;

    next_point = point;
    while (accuracy.depth_march-- && vec_len(vec_sub(point, next_point)) < accuracy.max_dist)
    {
        r = -1;
        counter = objs.number_objs;
        while (counter--)
        {
            r = update_r(r, objs.objs[counter], next_point);
            if (r < accuracy.delta && r != -1)
            {
                point_data.norm = get_normal(next_point, objs.objs[counter]);
                point_data.obj = &objs.objs[counter];
                point_data.point = next_point;
                return (point_data);
            }
        }
        next_point = vec_sum(next_point, vec_dotdec(vec, r));
    }
    point_data.norm = new_vec0();
    point_data.obj = 0;
    point_data.point = new_vec0();
    return (point_data);
}
