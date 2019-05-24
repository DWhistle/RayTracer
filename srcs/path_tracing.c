#include "ray_render.h"

t_point_data   path_tracing(t_scene scene, t_vec vec, t_accuracy accuracy, t_vec point)
{
    t_point_data point_data;

    point_data = raymarching(scene, vec, accuracy, point);
    if (point_data.obj)
    {
        point_data.color = vec_dotdec(point_data.obj->color, light_render(scene, point_data, point_data.norm));
        return (point_data);
    }
    return (point_data);
}
