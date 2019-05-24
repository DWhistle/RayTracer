#include "ray_render.h"

t_vec   get_ref_vec(t_point_data point_data, t_vec vec)
{
    ;
}

t_vec   get_ref_color(t_point_data *points)
{
    ;
}

t_vec   ray_render(t_scene scene, t_vec point, t_accuracy accuracy)
{
    int depth_ref;
    t_point_data point_data;
    t_point_data *points;
    t_vec color;

    point_data = path_tracing(scene, vec_norm(vec_sub(point, scene.cam)), accuracy, scene.cam);
    if(point_data.obj)
    {
        points = (t_point_data*)ft_memalloc(sizeof(t_point_data) * accuracy.depth_ref + 1);
        color = point_data.color;
        depth_ref = 0;
        while(accuracy.depth_ref > depth_ref && point_data.obj->reflection)
        {
            point_data = path_tracing(scene, get_ref_vec(), accuracy, point_data.point);
            points[depth_ref] = point_data;
        }
        color = get_ref_color(points);
        free(points);
        return(color);
    }
    return (new_vec0());
}
