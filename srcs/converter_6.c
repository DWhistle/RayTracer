/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_6.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:19:01 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 11:19:03 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

void		get_obj4(t_json *json, t_obj *object)
{
	int			res;

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
}

void		get_obj(t_json *obj, char *name, t_obj *object)
{
	int			res;
	t_json		*json;
	static int	n = 0;

	json = (t_json*)query_attribute(obj, name, &res).json_value;
	object->reflection = query_attribute(json, "reflection", &res).float_value;
	if (res)
		object->reflection = 0;
	object->refraction = query_attribute(json, "refraction", &res).float_value;
	if (res)
		object->refraction = 0;
	get_obj2(json, object);
	get_obj4(json, object);
	get_obj3(json, name, object);
	object->ind = n++;
}

int			check_names_obj(char *name)
{
	return (!ft_strncmp(name, "sphere", 6)\
			|| !ft_strncmp(name, "tor", 3)\
			|| !ft_strncmp(name, "plane", 5)\
			|| !ft_strncmp(name, "cylinder", 8)\
			|| !ft_strncmp(name, "box", 3)\
			|| !ft_strncmp(name, "octahedron", 10)\
			|| !ft_strncmp(name, "ellipsoid", 9)\
			|| !ft_strncmp(name, "capsule", 7)\
			|| !ft_strncmp(name, "triangular_prism", 16)\
			|| !ft_strncmp(name, "hexagonal_prism", 15)\
			|| !ft_strncmp(name, "cone", 4)\
			|| !ft_strncmp(name, "mandelbub", 9));
}

void		get_light(t_json *obj, char *name, t_light *light)
{
	int		res;
	t_json	*json;

	json = (t_json*)query_attribute(obj, name, &res).json_value;
	light->type = query_attribute(json, "type", &res).int_value;
	light->intensity = query_attribute(json, "intensity", &res).float_value;
	light->r = query_attribute(json, "radius", &res).float_value;
	light->point = get_vec(query_attribute(json, "point", &res).json_value);
	light->vec = get_vec(query_attribute(json, "vec", &res).json_value);
}

t_accuracy	get_accuracy(t_json *obj)
{
	t_accuracy	accuracy;
	t_json		*json;
	int			res;

	json = (t_json*)query_attribute(obj, "accuracy", &res).json_value;
	accuracy.delta = query_attribute(json, "delta", &res).float_value;
	accuracy.depth_pt = 0;
	accuracy.depth_march = query_attribute(json,\
										"depth raymarching", &res).int_value;
	accuracy.depth_ref = query_attribute(json,\
										"depth reflaction", &res).int_value;
	accuracy.max_dist = query_attribute(json, "max dist", &res).int_value;
	accuracy.rpp = query_attribute(json, "antialiasing", &res).int_value;
	return (accuracy);
}
