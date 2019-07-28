/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_objects.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:35:48 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/28 16:12:30 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_values	query_attribute(t_json *obj, char *name)
{
	int			i;
	t_values	empty;

	empty.int_value = 0;
	i = 0;
	while (obj->type[i] != 0)
	{
		if (!ft_strcmp(obj->key[i], name))
		{
			return (obj->value[i]);
		}
		i++;
	}
	return (empty);
}

t_vec		get_vec(t_json *json)
{
	t_vec vec;

	vec.arr[0] = query_attribute(json, "x").float_value;
	vec.arr[1] = query_attribute(json, "y").float_value;
	vec.arr[2] = query_attribute(json, "z").float_value;
	return (vec);
}

void		get_obj(t_json *obj, char *name, t_obj *object)
{
	t_json		*json;
	static int	n = 0;

	json = (t_json*)query_attribute(obj, name).json_value;
	object->reflection = query_attribute(json, "reflection").float_value;
	object->refraction = query_attribute(json, "refraction").float_value;
	object->color = get_vec(query_attribute(json, "color").json_value);
	object->angle = query_attribute(json, "angle").float_value;
	object->rot_vec = get_vec(query_attribute(json, "rot_vec").json_value);
	object->point = get_vec(query_attribute(json, "point").json_value);
	object->rad = query_attribute(json, "rad").float_value;
	get_primitives(json, name, object);
	get_intermediates(json, name, object);
	get_extras(json, name, object);
	object->ind = n++;
}
