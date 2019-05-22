#include <math.h>
#include "objects.h"
#include "libft.h"
#include <stdio.h>
#define MAX_Z 1920
#define E 0.0001

double len_circle(t_vec point, t_sphere *sphere)
{
    //printf("%f\n", vec_len(vec_sub(point, sphere->point)) - sphere->r);
    return (vec_len(vec_sub(point, sphere->point)) - sphere->r);
}

double len_cone(t_vec point, t_cone *cone)
{
    double q;
    q = vec_len(vec_sub(cone->point, point));
    return(vec_dotvec(cone->vec, new_vec2(q, point.arr[2])));
}

double len_cylinder(t_vec point, t_cylinder *cylinder)
{
    double  k;
    t_vec   vec;

    vec = vec_sub(point, cylinder->point);
    k = vec_dotvec(vec, cylinder->vec);
    return(vec_len(vec_sub(vec, vec_dotdec(cylinder->vec, k))) - cylinder->r);
}

double len_plane(t_vec point, t_plane *plane)
{
    return(fabs(plane->norm.arr[0] * point.arr[0] + \
           plane->norm.arr[1] * point.arr[1] + \
           plane->norm.arr[2] * point.arr[2] - \
           plane->norm.arr[0] * plane->point.arr[0] - \
           plane->norm.arr[1] * plane->point.arr[1] - \
           plane->norm.arr[2] * plane->point.arr[2])); 
}

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

t_vec light_render(t_scene objs, t_obj obj, t_vec point, t_vec *nr)
{
    double d = -1;
    t_vec l;
    t_vec n;
    double r = -1;
    double dif;
    int counter = objs.number_lights;
    double i = 0;

    while (counter--)
    {
        if (objs.lights[counter].type == AMBIENT)
            i += objs.lights[counter].intensity;
        if (objs.lights[counter].type == POINT)
        {
            l = vec_norm(vec_sub(objs.lights[counter].point, point));
            d = update_r(d, obj, point);
            n = new_vec3(d - update_r(r, obj, vec_sub(point, new_vec3(E, 0, 0))), d - update_r(r, obj, vec_sub(point, new_vec3(0, E, 0))), d - update_r(r, obj, vec_sub(point, new_vec3(0, 0, E))));
            n = vec_norm(n);
            dif = vec_dotvec(n, l);
            if (dif > 0)
                i += dif * objs.lights[counter].intensity;
        }
    }
    *nr = n;
    return (vec_dotdec(obj.color, i));
}

t_vec raymarching(t_scene objs, t_vec vec, int depth, double delta, double max_distance, t_vec point)
{
    double r;
    int counter;
    t_vec n;

    vec = vec_norm(vec);
    while (depth-- && vec_len(vec_sub(objs.cam, point)) < max_distance)
    {
        r = -1;
        counter = objs.number_objs;
        while (counter--)
        {
            r = update_r(r, objs.objs[counter], point);
            if (r < delta && r != -1)
                return(light_render(objs, objs.objs[counter], point, &n));
        }
        point = vec_sum(point, vec_dotdec(vec, r));
    }
    return (new_vec3(0, 0, 0));
}

void ray_render(t_scene scene, int **pixel, int h, int w)
{
    int x = w;
    int y = h;
    t_vec color;
    y = h;
    while(y--)
    {
        x = w;
        while(x--)
        {
            color = raymarching(scene, vec_sub(new_vec3(x - w/2, y - h/2, MAX_Z), scene.cam), 2000, 0.001, 10000, scene.cam);
            if (color.arr[0] > 255)
                color.arr[0] = 255;
            if (color.arr[1] > 255)
                color.arr[1] = 255;
            if (color.arr[2] > 255)
                color.arr[2] = 255;
            
            (*pixel)[x + w * y] = (int)(color.arr[0]) * 256 * 256 + (int)(color.arr[1]) * 256 +  (int)(color.arr[2]); 
        }
    }
}
