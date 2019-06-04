#include "ray_render.h"

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
