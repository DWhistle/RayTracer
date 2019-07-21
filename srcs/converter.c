/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:31:11 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/09 19:49:28 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
#include "parser.h"




void logger(t_obj *s){
    if (s->type == SPHERE){

    printf("%f %f %f %f \n", ((t_sphere *)s->obj)->r, 
     ((t_sphere *)s->obj)->point.arr[0],
     ((t_sphere *)s->obj)->point.arr[1],
     ((t_sphere *)s->obj)->point.arr[2]);
    }
    else if (s->type == PLANE){
        printf("======\nplane:\n  |point|%f %f %f\n  |norm| %f %f %f \n", 
     ((t_plane *)s->obj)->point.arr[0],
     ((t_plane *)s->obj)->point.arr[1],
     ((t_plane *)s->obj)->point.arr[2],
     ((t_plane *)s->obj)->norm.arr[0],
     ((t_plane *)s->obj)->norm.arr[1],
     ((t_plane *)s->obj)->norm.arr[2]);
    }
    else if(s->type == CYLINDER){
        printf("======\n cylinder:\n  |point|%f %f %f\n  |vec| %f %f %f \n r == %f\n", 
     ((t_cylinder *)s->obj)->point.arr[0],
     ((t_cylinder *)s->obj)->point.arr[1],
     ((t_cylinder *)s->obj)->point.arr[2],
     ((t_cylinder *)s->obj)->vec.arr[0],
     ((t_cylinder *)s->obj)->vec.arr[1],
     ((t_cylinder *)s->obj)->vec.arr[2],
     ((t_cylinder *)s->obj)->r);
    }
    else if (s->type == TOR){
        printf("======\n tor:\n  |point|%f %f %f\n  |norm| %f %f %f \n r == %f\n R == %f\n", 
        ((t_tor *)s->obj)->plane.point.arr[0],
        ((t_tor *)s->obj)->plane.point.arr[1],
        ((t_tor *)s->obj)->plane.point.arr[2],
        ((t_tor *)s->obj)->plane.norm.arr[0],
        ((t_tor *)s->obj)->plane.norm.arr[1],
        ((t_tor *)s->obj)->plane.norm.arr[2],
        ((t_tor *)s->obj)->r,
        ((t_tor *)s->obj)->R);
    }
}
t_values query_attribute(t_json *obj, char *name)
{
    int i;
    t_values empty;

    i = 0;
    while (obj->type[i] != 0)
    {
        
        if (!ft_strcmp(obj->key[i], name)){
        printf("attribute %s\n", obj->key[i]);
                    return obj->value[i];
        }
        i++;
    }
    return empty;
}

t_vec get_vec(t_json *json){
    t_vec vec;
    
    printf("get_vec");
    vec.arr[0] = query_attribute(json, "x").float_value;
    vec.arr[1] = query_attribute(json, "y").float_value;
    vec.arr[2] = query_attribute(json, "z").float_value;
    return (vec);
}

void    get_sphere(t_json *obj, t_obj *object)
{
    printf("obj\n");
    object->type = SPHERE;
    object->obj = ft_memalloc(sizeof(t_sphere));
    ((t_sphere*)object->obj)->point = get_vec(query_attribute(obj, "point").json_value);
    ((t_sphere*)object->obj)->r = query_attribute(obj, "radius").float_value;
   // printf("%f\n", ((t_sphere*)object->obj)->point.vec.z);
}

void    get_tor(t_json *obj, t_obj *object)
{
    object->type = TOR;
    object->obj = ft_memalloc(sizeof(t_tor));
    ((t_tor*)object->obj)->plane.norm = vec_norm(get_vec(query_attribute(obj, "norm").json_value));
    ((t_tor*)object->obj)->plane.point = get_vec(query_attribute(obj, "point").json_value);
    ((t_tor*)object->obj)->R = query_attribute(obj, "radius1").float_value;
    ((t_tor*)object->obj)->r = query_attribute(obj, "radius2").float_value;
}

void    get_plane(t_json *obj, t_obj *object)
{
    printf("plane\n");
    object->type = PLANE;
    printf("%p", obj);
    object->obj = ft_memalloc(sizeof(t_plane));
    ((t_plane*)object->obj)->norm = vec_norm(get_vec(query_attribute(obj, "norm").json_value));
    ((t_plane*)object->obj)->point = get_vec(query_attribute(obj, "point").json_value);
}

void    get_cylinder(t_json *obj, t_obj *object)
{
    printf("cylinder\n");
    object->type = CYLINDER;
    object->obj = ft_memalloc(sizeof(t_cylinder));
    ((t_cylinder*)object->obj)->point = get_vec(query_attribute(obj, "point").json_value);
    ((t_cylinder*)object->obj)->r = query_attribute(obj, "r").float_value;
     ((t_cylinder*)object->obj)->vec = vec_norm(get_vec(query_attribute(obj, "vector").json_value));
}

t_obj *get_obj(t_json *obj, char *name)
{
    t_json *json;
    t_obj *object;
    static int n = 0;
    
    json = (t_json*)query_attribute(obj, name).json_value;
    object = (t_obj*)ft_memalloc(sizeof(t_obj));
    object->reflection = query_attribute(obj, "reflection").float_value;
    object->refraction = query_attribute(obj, "refraction").float_value;
    object->color = get_vec(query_attribute(json, "color").json_value);
    if (ft_strncmp(name, "sphere", 6) == 0)
        get_sphere(json, object);
    else if (ft_strncmp(name, "tor", 3) == 0)
        get_tor(json, object);
    else if (ft_strncmp(name, "plane", 5) == 0)
        get_plane(json, object);
    else if (ft_strncmp(name, "cylinder", 8) == 0)
        get_cylinder(json, object);
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
    scene->bm = query_attribute(obj, "blur motion").int_value;
    scene->ce = query_attribute(obj, "cartoon effect").int_value;
    scene->neg = query_attribute(obj, "negative").int_value;
    scene->sepia = query_attribute(obj, "sepia").int_value;
    scene->ster = query_attribute(obj, "stereoscopy").int_value;
    return (scene);
}

void convert_objects(t_json *j)
{
    printf("%p\n", (void *)j);
    t_scene *sc = get_scene(j);
    t_obj *s = get_obj(j, "tor");
    logger(s);
    
     
    
    // t_obj *t = get_obj(j, "tor");
    // t_obj *pl1 = get_obj(j, "plane1");
    // t_obj *pl2 = get_obj(j,"plane2");
    // t_obj *pl3 = get_obj(j, "plane3");

}

