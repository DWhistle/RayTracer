/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:31:11 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/17 11:33:51 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "parser.h"

t_values query_attribute(t_json *obj, char *name)
{
    int i;
    t_values empty;
	empty.int_value = 0;

    i = 0;
    while (obj->type[i] != 0)
    {
        if (!ft_strcmp(obj->key[i], name))
            return obj->value[i];
        i++;
    }
    return empty;
}

t_vec get_vec(t_json *json){
    t_vec vec;
    
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
    printf("%f\n", ((t_sphere*)object->obj)->point.vec.z);
}

void    get_tor(t_json *obj, t_obj *object)
{
    object->type = TOR;
    object->obj = ft_memalloc(sizeof(t_tor));
    ((t_tor*)object->obj)->plane.norm = vec_norm(get_vec(query_attribute(obj, "norm").json_value));
    ((t_tor*)object->obj)->plane.norm = get_vec(query_attribute(obj, "point").json_value);
    ((t_tor*)object->obj)->R = query_attribute(obj, "radius1").float_value;
    ((t_tor*)object->obj)->r = query_attribute(obj, "radius2").float_value;
}

void    get_plane(t_json *obj, t_obj *object)
{
    object->type = PLANE;
    object->obj = ft_memalloc(sizeof(t_plane));
    ((t_plane*)object->obj)->norm = vec_norm(get_vec(query_attribute(obj, "norm").json_value));
    ((t_plane*)object->obj)->norm = get_vec(query_attribute(obj, "point").json_value);
}

void    get_cylinder(t_json *obj, t_obj *object)
{
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
    if (ft_strncmp(name, "sphere", 7))
        get_sphere(json, object);
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
    scene->bm = query_attribute(obj, "blur motion").int_value;
    scene->ce = query_attribute(obj, "cartoon effect").int_value;
    scene->neg = query_attribute(obj, "negative").int_value;
    scene->sepia = query_attribute(obj, "sepia").int_value;
    scene->ster = query_attribute(obj, "stereoscopy").int_value;
    return (scene);
}

int		check_names(char *name)
{
	return (ft_strncmp(name, "sphere", 7) || ft_strncmp(name, "tor", 3)\
			|| ft_strncmp(name, "plane", 5) || ft_strncmp(name, "cylinder", 8));
}

char	**gate_names_obj(t_json *j)
{
	int i;
	int k;
	char** names;

	i = 0;
	k = 0;
	while (j->key[i])
		if (check_names(j->key[i++]))
			k++;
	names = ft_memalloc(sizeof(char*) * (k + 1));
	i = 0;
	k = 0;
	while (j->key[i])
		if (check_names(j->key[i++]))
            {
				names[k] = ft_strdup(j->key[i]);
				k++;
			}
    return (names);
}

void *convert_objects(t_json *j)
{
    char **names_obj;
	t_vec v = get_vec(query_attribute(j, "color").json_value);

    printf("%p\n", (void *)j);
    t_scene *sc = get_scene(j);
	printf("bm = %f\n", v.arr[1]);
    t_obj *s = get_obj(j, "sphere1");
    printf("%f\n %f\n %f\n %f \n", ((t_sphere *)s->obj)->r, 
    s->color.arr[0],
    s->color.arr[1],
    s->color.arr[2]);
	return (sc);
	names_obj = gate_names_obj(j);
    
    //t_obj *t = get_obj(j, "tor");
    //t_obj *pl1 = get_obj(j, "plane1");
    //t_obj *pl2 = get_obj(j,"plane2");
    //t_obj *pl3 = get_obj(j, "plane3");
    return (sc);
}
