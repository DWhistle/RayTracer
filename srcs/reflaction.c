#include "ray_render.h"

t_vec   get_ref_vec(t_point_data point_data, t_vec vec)
{
    vec = vec_dotdec(vec, -1);
    vec = vec_sub(vec_dotdec(point_data.norm, vec_dotvec(point_data.norm, vec) * 2), vec);
    vec = vec_norm(vec);
    return (vec);
}

t_vec   get_ref_color(t_point_data *points)
{
    int i;
    t_vec color_ref;
    t_vec color;
    double ref;

    i = 0;
    while(points[i].obj)
    {
        i++;
        ft_putnbr(i);
        ft_putendl("");
    }
    while(i-- != 1)
    {
        ft_putnbr(i);
        ft_putendl("");
        color_ref = points[i].color;
        ref = points[i-1].obj->reflection;
        color = points[i-1].color;
        color = vec_sum(vec_dotdec(color, 1 - ref), vec_dotdec(color_ref, ref));
        points[i-1].color = color;
        ft_putnbr(i);
        ft_putendl("");
    }
    ft_putendl("");
    return(points[0].color);
}

t_vec   ray_render(t_scene scene, t_vec point, t_accuracy accuracy)
{
    int depth_ref;
    t_point_data point_data;
    t_point_data *points;
    t_vec color;
    t_vec vec;

    vec = vec_norm(vec_sub(point, scene.cam));
    point_data = path_tracing(scene, vec, accuracy, scene.cam);
    
    if(point_data.obj)
    {
        points = (t_point_data*)ft_memalloc(sizeof(t_point_data) * (accuracy.depth_ref + 1));
        points[0] = point_data;
        depth_ref = 0;
        ft_putnbr(999999);
        ft_putendl("");
        ft_putendl("");
        while(accuracy.depth_ref > depth_ref++ && point_data.obj->reflection)
        {
            scene.ignore = point_data.obj;
            point_data = path_tracing(scene, get_ref_vec(point_data, vec), accuracy, point_data.point);
            points[depth_ref] = point_data;
        }
        points[depth_ref].obj = 0;
        ft_putnbr(3534535);
        ft_putendl("");
        color = get_ref_color(points);
        free(points);
        return(color);
    }
    return (new_vec0());
}