#include "ray_render.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

t_vec           rand_vec(double x, double y, double z)
{
    if (x == 0)
        x = (rand() % 10000) - 5000;
    else
        x = (rand() % 10000) * x;
    if (y == 0)
        y = (rand() % 10000) - 5000;
    else
        y = (rand() % 10000) * y;
    if (z == 0)
        z = (rand() % 10000) - 5000;
    else
        z = (rand() % 10000) * z;
    return (vec_norm(new_vec3(x, y, z)));
}

t_point_data    path_tracing(t_scene scene, t_vec vec, t_accuracy accuracy, t_vec point)
{
    t_point_data point_data;
    t_point_data point_data2;
    int depth_pt;
    t_vec norm;

    depth_pt = 0;
    point_data = raymarching(scene, vec, accuracy, point);
    point_data2 = point_data;
    if (point_data.obj)
    {
        while(accuracy.depth_pt > depth_pt++)
        {
            scene.ignore = point_data2.obj;
            norm = point_data2.norm;
            point_data2 = raymarching(scene, rand_vec(norm.arr[0], norm.arr[1], norm.arr[2]), accuracy, point);
            if (point_data2.obj && point_data2.obj->ind == 4)
            {
                point_data.color = vec_dotdec(point_data.obj->color, 1.0 / depth_pt);
                break;
            }
        }
    }
    return (point_data);
}
