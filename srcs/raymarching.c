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

void update_r(double *r, t_obj new_obj, t_obj *obj, t_vec point)
{
    double len;
    if (new_obj.type == CIRCLE)
        len = len_circle(point, new_obj);
    if(*r == -1 || len < *r)
    {
        *obj = new_obj; 
        *r = len;
    }
}

int light_render(t_scene objs, t_obj obj)
{
    if (objs.lights->type == DIRECT)
    {
        return (obj.color);
    }
    return (0);
}

int raymarching(t_scene objs, t_vec vec, int depth, double delta)
{
    double r;
    t_vec point;
    t_obj obj;
    int counter;

    r = -1;
    point = objs.cam;
    vec = vec_norm(vec);
    while (depth--)
    {
        counter = objs.number_objs;
        while (counter--)
            update_r(&r, objs.objs[counter], &obj, point);
        if (r < delta)
            return (light_render(objs, obj));
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
