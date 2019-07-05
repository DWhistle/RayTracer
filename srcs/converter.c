/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:31:11 by bturcott          #+#    #+#             */
/*   Updated: 2019/06/30 16:08:04 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "parser.h"

char **get_names(t_json *obj);

int get_int(void *value)
{
    return ((int *)value)[0];
}

float get_float(void *value)
{
    return (((float *)value)[0]);
}

float *get_float_array(void *value){
    return ((float *)value);
}

int *get_int_array(void *value){
    return ((int *)value);
}

char *get_string(void *value){
    return ((char*)value);
}

t_vec get_vec(t_json *json){
    t_vec vec;
    
    vec.arr[0] = *((double*)json->value[0]);
    vec.arr[1] = *((double*)json->value[1]);
    vec.arr[2] = *((double*)json->value[2]);
    return (vec);
}

char **get_string_array(void *value){
    return ((char **)value);
}

void *query_attribute(t_json *obj, char *name)
{
    int i;

    i = 0;

    while (obj->type[i] != 0)
    {
        if (!ft_strcmp(obj->key[i], name))
            return obj->value[i];
        i++;
    }
    return NULL;
}

void    get_sphere(t_json *obj, t_obj *object)
{
    object->type = SPHERE;
    object->obj = ft_memalloc(sizeof(t_sphere));
    ((t_sphere*)object->obj)->point = get_vec(query_attribute(obj, "point"));
    ((t_sphere*)object->obj)->r = *((double*)query_attribute(obj, "radius"));
}

void    get_tor(t_json *obj, t_obj *object)
{
    object->type = TOR;
    object->obj = ft_memalloc(sizeof(t_tor));
    ((t_tor*)object->obj)->plane.norm = vec_norm(get_vec(query_attribute(obj, "norm")));
    ((t_tor*)object->obj)->plane.norm = get_vec(query_attribute(obj, "point"));
    ((t_tor*)object->obj)->R = *((double*)query_attribute(obj, "radius1"));
    ((t_tor*)object->obj)->r = *((double*)query_attribute(obj, "radius2"));
}

void    get_plane(t_json *obj, t_obj *object)
{
    object->type = PLANE;
    object->obj = ft_memalloc(sizeof(t_plane));
    ((t_plane*)object->obj)->norm = vec_norm(get_vec(query_attribute(obj, "norm")));
    ((t_plane*)object->obj)->norm = get_vec(query_attribute(obj, "point"));
}

void    get_cylinder(t_json *obj, t_obj *object)
{
    object->type = CYLINDER;
    object->obj = ft_memalloc(sizeof(t_cylinder));
    ((t_cylinder*)object->obj)->point = get_vec(query_attribute(obj, "point"));
    ((t_cylinder*)object->obj)->r = *((double*)query_attribute(obj, "r"));
     ((t_cylinder*)object->obj)->vec = vec_norm(get_vec(query_attribute(obj, "vector")));
}

t_obj *get_obj(t_json *obj, char *name)
{
    t_json *json;
    t_obj *object;
    static int n = 0;
    
    json = (t_json*)query_attribute(obj, name);
    object = (t_obj*)ft_memalloc(sizeof(t_obj));
    object->reflection = *((double*)query_attribute(obj, "reflection"));
    object->refraction = *((double*)query_attribute(obj, "refraction"));
    object->color = get_vec(query_attribute(obj, "color"));
    if (ft_strncmp(name, "sphere", 6))
        get_sphere(obj, object);
    else if (ft_strncmp(name, "tor", 3))
        get_tor(obj, object);
    else if (ft_strncmp(name, "plane", 5))
        get_plane(obj, object);
    else if (ft_strncmp(name, "cylinder", 8))
        get_cylinder(obj, object);
    else
        return (NULL);
    object->ind = n++;
    return (object);
}

t_scene *get_scene(t_json *obj)
{
    t_scene *scene;

    scene = (t_scene*)ft_memalloc(sizeof(t_scene));
    scene->cam = new_vec3(0, 0, 0);
    scene->ignore = NULL;
    scene->bm = *((int*)query_attribute(obj, "blur motion"));
    scene->ce = *((int*)query_attribute(obj, "cartoon effect"));
    scene->neg = *((int*)query_attribute(obj, "negative"));
    scene->sepia = *((int*)query_attribute(obj, "sepia"));
    scene->ster = *((int*)query_attribute(obj, "stereoscopy"));
    return (scene);
}
