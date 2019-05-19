#include <math.h>
#include "objects.h"
#include "libft.h"
#include <stdio.h>
#define MAX_Z 1000

double len_circle(t_vec point, t_obj circle)
{
    t_vec x;
    x = vec_sub(point, circle.point);
    return (sqrt(vec_sqrdist(x)) - circle.r);
}

double update_r(double r, t_obj new_obj, t_obj *obj, t_vec point)
{
    double len;
    if (new_obj.type == CIRCLE)
        len = len_circle(point, new_obj);
    if(r == -1 || len < r)
    {
        *obj = new_obj; 
        r = len;
    }
    return (r);
}

int light_render(t_scene objs, t_obj obj, t_vec point)
{
    double d = -1;
    t_vec l;
    t_vec n;
    t_vec nl;
    t_vec e;
    t_vec e1;
    t_vec e2;
    double r = -1;
    double dif;
    if (objs.lights->type == DIRECT)
    {
        l = vec_sub(objs.lights->point, point);
        d = update_r(d, obj, &obj, point);
        e = new_vec3(0.01, 0, 0);
        e1 = new_vec3(0, 0.01, 0);
        e2 = new_vec3(0, 0, 0.01);
        n = new_vec3(d - update_r(r, obj, &obj, vec_sub(point, e)), d - update_r(r, obj, &obj, vec_sub(point, e1)), d - update_r(r, obj, &obj, vec_sub(point, e2)));
        n = vec_norm(n);
        nl = vec_dotvec(n, l);
        dif = nl.arr[0] + nl.arr[1] + nl.arr[2];
        if (dif > 0)
            return (200 * 256 * dif / vec_len(l));
    }
    return (0);
}

int raymarching(t_scene objs, t_vec vec, int depth, double delta)
{
    double r = 0;
    t_vec point;
    t_obj obj;
    int counter;

    point = objs.cam;
    vec = vec_norm(vec);
    while (depth--)
    {
        r = -1;
        counter = objs.number_objs;
        while (counter--)
            r = update_r(r, objs.objs[counter], &obj, point);
        if (r < delta)
            return (light_render(objs, obj, point));
        point = vec_sum(point, vec_dotdec(vec, r));
    }
    return (0);
}

void ray_render(t_scene scene, int **pixel, int h, int w)
{
    int x = w;
    int y = h;
    int color;
    y = h;
    while(y--)
    {
        x = w;
        while(x--)
        {
            color = raymarching(scene, vec_sub(new_vec3(x - w/2, y - h/2, MAX_Z), scene.cam), 5, 0.1);
            (*pixel)[x + w * y] = color;
        }
    }
}
