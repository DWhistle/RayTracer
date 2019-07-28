/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_extras.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:31:46 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/28 16:09:56 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_ellipsoid(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_ellipsoid;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_octahedron(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_octahedron;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_box(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_box;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_extras(t_json *json, char *name, t_obj *object)
{
	if (ft_strncmp(name, "ellipsoid", 9) == 0)
		get_ellipsoid(json, object);
	else if (ft_strncmp(name, "octahedron", 10) == 0)
		get_octahedron(json, object);
	else if (ft_strncmp(name, "box", 3) == 0)
		get_box(json, object);
}
