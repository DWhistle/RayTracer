/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:19:10 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/09 15:48:20 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

int			get_cylinder(t_json *json, t_obj *object)
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

int			get_plane(t_json *json, t_obj *object)
{
	int		res;

	object->type = PLANE;
	object->len = len_plane;
	object->param = new_vec0();
	object->param = vec_norm(get_vec(\
	query_attribute(json, "param", &res).json_value));
	if (res)
		object->param = new_vec0();
	return (res);
}

int			get_tor(t_json *json, t_obj *object)
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

int			get_hexagonal_prism(t_json *json, t_obj *object)
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

int			get_triangular_prism(t_json *json, t_obj *object)
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
