/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:19:12 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 11:19:13 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

int			gate_names_obj(t_json *j, char ***names, int (*check_names)())
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

t_values	query_attribute(t_json *obj, char *name, int *res)
{
	int			i;
	t_values	empty;

	empty.int_value = 0;
	i = 0;
	while (obj->type[i] != 0)
	{
		if (!ft_strcmp(obj->key[i], name))
		{
			*res = 0;
			return (obj->value[i]);
		}
		i++;
	}
	*res = -1;
	return (empty);
}

t_vec		get_vec(t_json *json)
{
	t_vec	vec;
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

int			get_sphere(t_json *json, t_obj *object)
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

int			get_cone(t_json *json, t_obj *object)
{
	int		res;

	object->type = CONE;
	object->len = len_cone;
	object->param = vec_norm(get_vec(\
	query_attribute(json, "param", &res).json_value));
	if (res)
		object->param = new_vec0();
	return (res);
}
