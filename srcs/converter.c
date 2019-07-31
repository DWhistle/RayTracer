/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:31:11 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "parser.h"
#include "SDL2/SDL.h"
#define PI 3.14159265359

t_values query_attribute(t_json *obj, char *name)
{
    int i;
    t_values empty;
	empty.int_value = 0;

    i = 0;
    while (obj->type[i] != 0)
    {
        
        if (!ft_strcmp(obj->key[i], name)){
                    return obj->value[i];
        }
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

void    get_sphere(t_json *json, t_obj *object)
{
    object->type = SPHERE;
    object->len = len_sphere;
    object->param = new_vec0();
    object->param.arr[0] = query_attribute(json, "radius").float_value;
}

void    get_cone(t_json *json, t_obj *object)
{
    object->type = CONE;
    object->len = len_cone;   
    object->param = vec_norm(get_vec(query_attribute(json, "param").json_value));
}

void    get_cylinder(t_json *json, t_obj *object)
{
    object->type = CYLINDER;
    object->len = len_cylinder;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param").json_value);
}

void    get_plane(t_json *json, t_obj *object)
{
    object->type = PLANE;
    object->len = len_plane;
    object->param = new_vec0();
    object->param = vec_norm(get_vec(query_attribute(json, "param").json_value));
}

void    get_tor(t_json *json, t_obj *object)
{
    object->type = TOR;
    object->len = len_tor;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param").json_value);
}

void    get_hexagonal_prism(t_json *json, t_obj *object)
{
    object->type = HEXAGONAL_PRISM;
    object->len = len_hexagonal_prism;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param").json_value);
}

void    get_triangular_prism(t_json *json, t_obj *object)
{
    object->type = TRIANGULAR_PRISM;
    object->len = len_triangular_prism;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param").json_value);
}

void    get_capsule(t_json *json, t_obj *object)
{
    object->type = CAPSULE;
    object->len = len_capsule;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param").json_value);
}

void    get_ellipsoid(t_json *json, t_obj *object)
{
    object->type = ELLIPSOID;
    object->len = len_ellipsoid;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param").json_value);
}

void    get_octahedron(t_json *json, t_obj *object)
{
    object->type = OCTAHEDRON;
    object->len = len_octahedron;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param").json_value);
}

void    get_box(t_json *json, t_obj *object)
{
    object->type = BOX;
    object->len = len_box;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param").json_value);
}

t_texture   get_texture(char *image, t_json *j)
{
    SDL_Surface *serf;
    t_texture   tex;
    if (!(serf = SDL_LoadBMP(image)))
    {
        tex.texture = NULL;
        return (tex);
    }
    tex.texture = serf->pixels;
    tex.h = serf->h;
    tex.w = serf->w;
    tex.len_u = query_attribute(j, "len_u").float_value;
    tex.len_v = query_attribute(j, "len_v").float_value;
    return (tex);
}

void    get_obj(t_json *obj, char *name, t_obj *object)
{
    t_json *json;
    static int n = 0;
    
    json = (t_json*)query_attribute(obj, name).json_value;
    object->reflection = query_attribute(json, "reflection").float_value;
    object->refraction = query_attribute(json, "refraction").float_value;
    object->color = get_vec(query_attribute(json, "color").json_value);
    object->rot_quat = create_quat(vec_norm(get_vec(query_attribute(json, "rot_vec").json_value)),\
                        query_attribute(json, "angle").float_value);
    object->point = get_vec(query_attribute(json, "point").json_value);
    object->rad = query_attribute(json, "rad").float_value;
    object->neg = query_attribute(json, "neg").int_value;
    object->fract = query_attribute(json, "fract").float_value;
    object->texture = get_texture(query_attribute(json, "texture").string_value, json);
    if (ft_strncmp(name, "sphere", 6) == 0)
        get_sphere(json, object);
    else if (ft_strncmp(name, "cone", 4) == 0)
        get_cone(json, object);
    else if (ft_strncmp(name, "cylinder", 8) == 0)
        get_cylinder(json, object);
    else if (ft_strncmp(name, "plane", 5) == 0)
        get_plane(json, object);
    else if (ft_strncmp(name, "tor", 3) == 0)
        get_tor(json, object);
    else if (ft_strncmp(name, "hexagonal_prism", 15) == 0)
        get_hexagonal_prism(json, object);
    else if (ft_strncmp(name, "triangular_prism", 16) == 0)
        get_triangular_prism(json, object);
    else if (ft_strncmp(name, "capsule", 7) == 0)
        get_capsule(json, object);
    else if (ft_strncmp(name, "ellipsoid", 9) == 0)
        get_ellipsoid(json, object);
    else if (ft_strncmp(name, "octahedron", 10) == 0)
        get_octahedron(json, object);
    else if (ft_strncmp(name, "box", 3) == 0)
        get_box(json, object);
    else
        return ;
    object->ind = n++;
}

int		check_names_obj(char *name)
{
	return (!ft_strncmp(name, "sphere", 6) || !ft_strncmp(name, "tor", 3)\
			|| !ft_strncmp(name, "plane", 5) || !ft_strncmp(name, "cylinder", 8)\
            || !ft_strncmp(name, "box", 3) || !ft_strncmp(name, "octahedron", 10)\
            || !ft_strncmp(name, "ellipsoid", 9) || !ft_strncmp(name, "capsule", 7)\
            || !ft_strncmp(name, "triangular_prism", 16) || !ft_strncmp(name, "hexagonal_prism", 15)\
            || !ft_strncmp(name, "cone", 4));
}

void    get_light(t_json *obj, char *name, t_light *light)
{
    t_json *json;
    
    json = (t_json*)query_attribute(obj, name).json_value;
    light->type = query_attribute(json, "type").int_value;
    light->intensity = query_attribute(json, "intensity").float_value;
    light->r = query_attribute(json, "radius").float_value;
    light->point = get_vec(query_attribute(json, "point").json_value);
    light->vec = get_vec(query_attribute(json, "vec").json_value);
}

t_accuracy  get_accuracy(t_json *obj)
{
    t_accuracy  accuracy;
    t_json      *json;

    json = (t_json*)query_attribute(obj, "accuracy").json_value;
    accuracy.delta = query_attribute(json, "delta").float_value;
    accuracy.depth_pt = 0;
    accuracy.depth_march = query_attribute(json, "depth raymarching").int_value;
    accuracy.depth_ref = query_attribute(json, "depth reflaction").int_value;
    accuracy.max_dist = query_attribute(json, "max dist").int_value;
    accuracy.rpp = query_attribute(json, "antialiasing").int_value;
    return (accuracy);
}

t_scene *get_scene(t_json *obj)
{
    t_scene *scene;

    scene = (t_scene*)ft_memalloc(sizeof(t_scene));
    scene->cam = new_vec3(0, 0, 0);
    scene->ignore = NULL;
    scene->w = query_attribute(obj, "w").int_value;
    scene->h = query_attribute(obj, "h").int_value;
    scene->bm = query_attribute(obj, "blur motion").int_value;
    scene->ce = query_attribute(obj, "cartoon effect").int_value;
    scene->neg = query_attribute(obj, "negative").int_value;
    scene->sepia = query_attribute(obj, "sepia").int_value;
    scene->ster = query_attribute(obj, "stereoscopy").int_value;
    scene->color = ft_memalloc(sizeof(t_vec) * scene->w * scene->w);
    scene->points_data = ft_memalloc(sizeof(t_point_data) * scene->w * scene->h);
    scene->accuracy = get_accuracy(obj);
    scene->FOW = query_attribute(obj, "FOW").float_value * (PI / 180.0);
    return (scene);
}

int		check_names_light(char *name)
{
	return (!ft_strncmp(name, "light", 4));
}

int     gate_names_obj(t_json *j, char*** names, int (*check_names)())
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (j->key[i])
    {
		if (check_names(j->key[i]))
			k++;
        i++;
    }
	*names = ft_memalloc(sizeof(char*) * (k + 1));
	i = 0;
	k = 0;
	while (j->key[i])
    {
		if (check_names(j->key[i]))
            {
				(*names)[k] = ft_strdup(j->key[i]);
				k++;
			}
        i++;
    }
    return (k);
}

void *convert_objects(t_json *j)
{
    int i;
    char **obj;
    t_scene *sc = get_scene(j);
    
    sc->number_objs = gate_names_obj(j, &obj, check_names_obj);
    sc->objs = ft_memalloc(sizeof(t_obj) * sc->number_objs);
    i = 0;
    while(i != sc->number_objs)
    {
        get_obj(j, obj[i], sc->objs + i);
        i++;
    }
    sc->number_lights = gate_names_obj(j, &obj, check_names_light);
    sc->lights = ft_memalloc(sizeof(t_obj) * sc->number_lights);
    i = 0;
    while(i != sc->number_lights)
    {
        get_light(j, obj[i], sc->lights + i);
        i++;
    }
    return (sc);
}

