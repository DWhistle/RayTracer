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

t_values query_attribute(t_json *obj, char *name, int *res)
{
    int i;
    t_values empty;
	empty.int_value = 0;

    i = 0;
    while (obj->type[i] != 0)
    {
        if (!ft_strcmp(obj->key[i], name)){
                    *res = 0;
                    return obj->value[i];
        }
        i++;
    }
    *res = -1;
    return empty;
}

t_vec get_vec(t_json *json){
    t_vec vec;
    int		res;
    
	if (!json)
		return (new_vec0());
    vec.arr[0] = query_attribute(json, "x", &res).float_value;
	if (res)
		vec.arr[0] = 0;
    vec.arr[1] = query_attribute(json, "y", &res).float_value;
	if (res)
		vec.arr[1] = 0;
    vec.arr[2] = query_attribute(json, "z", &res).float_value;
	if (res)
		vec.arr[2] = 0;
	vec.arr[3] = query_attribute(json, "w", &res).float_value;
	if (res)
		vec.arr[3] = 0;
    return (vec);
}

int    get_sphere(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = SPHERE;
    object->len = len_sphere;
    object->param = new_vec0();
    object->param.arr[0] = query_attribute(json, "radius", &res).float_value;
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_cone(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = CONE;
    object->len = len_cone;   
    object->param = vec_norm(get_vec(query_attribute(json, "param", &res).json_value));
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_cylinder(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = CYLINDER;
    object->len = len_cylinder;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_plane(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = PLANE;
    object->len = len_plane;
    object->param = new_vec0();
    object->param = vec_norm(get_vec(query_attribute(json, "param", &res).json_value));
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_tor(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = TOR;
    object->len = len_tor;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_hexagonal_prism(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = HEXAGONAL_PRISM;
    object->len = len_hexagonal_prism;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_triangular_prism(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = TRIANGULAR_PRISM;
    object->len = len_triangular_prism;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_capsule(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = CAPSULE;
    object->len = len_capsule;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_ellipsoid(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = ELLIPSOID;
    object->len = len_ellipsoid;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_octahedron(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = OCTAHEDRON;
    object->len = len_octahedron;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}

int    get_box(t_json *json, t_obj *object)
{
	int		res;
    
    object->type = BOX;
    object->len = len_box;
    object->param = new_vec0();
    object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}

t_texture   get_texture(t_json *j, char *name)
{
	int		res;
    SDL_Surface *serf;
    t_texture   tex;
    t_json      *json;
	char		*path;

	tex.texture = NULL;
    json = (t_json*)query_attribute(j, name, &res).json_value;
	if (res)
        return (tex);
	path = query_attribute(json, "path", &res).string_value;
	if (res)
        return (tex);
    if (!(serf = SDL_LoadBMP(path)))
        return (tex);
    tex.texture = serf->pixels;
    tex.h = serf->h;
    tex.w = serf->w;
    tex.len_u = query_attribute(json, "len_u", &res).float_value;
	if (res)
        tex.len_u = tex.h;
    tex.len_v = query_attribute(json, "len_v", &res).float_value;
	if (res)
        tex.len_v = tex.w;
    return (tex);
}

int				check_plane(char *name)
{
	return (!ft_strncmp(name, "plane", 5));
}

t_restriction	*get_restriction(t_json *j, int *ns_p)
{
	int				res;
    t_json      	*json;
	char			**names;
	t_restriction	*restriction;
	int				n;

    json = (t_json*)query_attribute(j, "restriction", &res).json_value;
	if (res)
		return (NULL);
	res = gate_names_obj(json, &names, check_plane);
	if (!(restriction = ft_memalloc(sizeof(t_restriction) * res)))
		return (NULL);
	n = res;
	*ns_p = res;
	while (n--)
	{
		j = (t_json*)query_attribute(json, names[n], &res).json_value;
		if (!res)
		{
			restriction[0].dislocation = get_vec(query_attribute(j, "dislocation", &res).json_value);
			if (res)
				restriction[n].dislocation = new_vec0();
			restriction[n].norm = vec_norm(get_vec(query_attribute(j, "norm", &res).json_value));
			if (res)
				restriction[n].norm = new_vec0();
		}
	}
	return (restriction);
}

void    get_obj(t_json *obj, char *name, t_obj *object)
{
	int		res;
    t_json *json;
    static int n = 0;
	double angle;
	t_vec rotvec;
    
    json = (t_json*)query_attribute(obj, name, &res).json_value;
    object->reflection = query_attribute(json, "reflection", &res).float_value;
	if (res)
		object->reflection = 0;
    object->refraction = query_attribute(json, "refraction", &res).float_value;
	if (res)
		object->refraction = 0;
	object->frequency = query_attribute(json, "frequency", &res).float_value;
	if (res)
		object->frequency = 0;
    object->amplitude = query_attribute(json, "amplitude", &res).float_value;
	if (res)
		object->amplitude = 0;
    object->color = get_vec(query_attribute(json, "color", &res).json_value);
	if (res)
		object->color = new_vec0();
	angle = query_attribute(json, "angle", &res).float_value;
	if (res)
		angle = 0;
	rotvec = get_vec(query_attribute(json, "rot_vec", &res).json_value);
	if (res)
		rotvec = new_vec0();
    object->rot_quat = create_quat(vec_norm(rotvec), angle);
    object->point = get_vec(query_attribute(json, "point", &res).json_value);
	if (res)
		object->point = new_vec0();
    object->rad = query_attribute(json, "rad", &res).float_value;
	if (res)
		object->rad = 0;
    object->neg = query_attribute(json, "neg", &res).int_value;
	if (res)
		object->neg = 0;
    object->fract = query_attribute(json, "fract", &res).float_value;
	if (res)
		object->fract = 0;
    object->specular = query_attribute(json, "specular", &res).int_value;
	if (res)
		object->specular = 0;
    object->normal_map = get_texture(json, "normal_map");
    object->texture = get_texture(json, "texture");
	object->restriction = get_restriction(json, &object->numbers_plane);
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
	int		res;
    t_json *json;
    
    json = (t_json*)query_attribute(obj, name, &res).json_value;
    light->type = query_attribute(json, "type", &res).int_value;
    light->intensity = query_attribute(json, "intensity", &res).float_value;
    light->r = query_attribute(json, "radius", &res).float_value;
    light->point = get_vec(query_attribute(json, "point", &res).json_value);
    light->vec = get_vec(query_attribute(json, "vec", &res).json_value);
}

t_accuracy  get_accuracy(t_json *obj)
{
    t_accuracy  accuracy;
    t_json      *json;
	int		res;
    
    json = (t_json*)query_attribute(obj, "accuracy", &res).json_value;
    accuracy.delta = query_attribute(json, "delta", &res).float_value;
    accuracy.depth_pt = 0;
    accuracy.depth_march = query_attribute(json, "depth raymarching", &res).int_value;
    accuracy.depth_ref = query_attribute(json, "depth reflaction", &res).int_value;
    accuracy.max_dist = query_attribute(json, "max dist", &res).int_value;
    accuracy.rpp = query_attribute(json, "antialiasing", &res).int_value;
    return (accuracy);
}

t_scene *get_scene(t_json *obj)
{
    t_scene *scene;
	int		res;
    
    scene = (t_scene*)ft_memalloc(sizeof(t_scene));
    scene->cam = new_vec3(0, 0, 0);
    scene->ignore = NULL;
    scene->w = query_attribute(obj, "w", &res).int_value;
    scene->h = query_attribute(obj, "h", &res).int_value;
    scene->bm = query_attribute(obj, "blur motion", &res).int_value;
    scene->ce = query_attribute(obj, "cartoon effect", &res).int_value;
    scene->neg = query_attribute(obj, "negative", &res).int_value;
    scene->sepia = query_attribute(obj, "sepia", &res).int_value;
    scene->ster = query_attribute(obj, "stereoscopy", &res).int_value;
    scene->color = ft_memalloc(sizeof(t_vec) * scene->w * scene->w);
    scene->points_data = ft_memalloc(sizeof(t_point_data) * scene->w * scene->h);
    scene->accuracy = get_accuracy(obj);
    scene->FOW = query_attribute(obj, "FOW", &res).float_value * (PI / 180.0);
    return (scene);
}

int		check_names_light(char *name)
{
	return (!ft_strncmp(name, "light", 4));
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

