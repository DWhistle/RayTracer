/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:19:09 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/09 16:10:58 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

int			get_capsule(t_json *json, t_obj *object)
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

int			get_ellipsoid(t_json *json, t_obj *object)
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

int			get_octahedron(t_json *json, t_obj *object)
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

int			get_box(t_json *json, t_obj *object)
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

int			get_mandelbub(t_json *json, t_obj *object)
{
	int		res;

	object->type = MANDELBUB;
	object->len = len_mandelbub;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}
