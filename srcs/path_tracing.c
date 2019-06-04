#include "ray_render.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

t_vec           rand_vec(t_vec vec)
{
    if (vec.arr[0] == 0)
        vec.arr[0] = (rand() % 200000 + 1) * ((double)(rand() % 2) - 0.5);
    else
        vec.arr[0] = (rand() % 100000 + 1) * vec.arr[0];
    if (vec.arr[1] == 0)
        vec.arr[1] = (rand() % 200000 + 1) * ((double)(rand() % 2) - 0.5);
    else
        vec.arr[1] = (rand() % 100000 + 1) * vec.arr[1];
    if (vec.arr[2] == 0)
        vec.arr[2] = (rand() % 200000 + 1) * ((double)(rand() % 2) - 0.5);
    else
        vec.arr[2] = (rand() % 100000 + 1) * vec.arr[2];
    return (vec_norm(vec));
}

int is_light(t_scene scene, int ind)
{
    int counter = 0;

    while(counter != scene.number_lights)
    {
        if (scene.lights[counter].ind = ind)
            return(1);
        counter++;
    }
    return (0);
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
    while(accuracy.depth_pt > depth_pt++ && point_data2.obj)
    {
        scene.ignore = point_data2.obj;
        norm = point_data2.norm;
        if (point_data2.obj && is_light(scene, point_data2.obj->ind))
        {
            scene.ignore = 0;
            point_data.color = vec_dotdec(point_data.obj->color, 1.0 / depth_pt);
            break;
        }
        point_data2 = raymarching(scene, rand_vec(norm), accuracy, point);
    }
    return (point_data);
}
