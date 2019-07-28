/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_primitives.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 13:45:51 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/28 14:55:42 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_sphere(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_sphere;
	object->param = new_vec0();
	object->param.arr[0] = query_attribute(json, "radius").float_value;
}

void	get_cone(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_cone;
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_cylinder(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_cylinder;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_plane(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_plane;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_primitives(t_json *json, char *name, t_obj *object)
{
	if (ft_strncmp(name, "sphere", 6) == 0)
		get_sphere(json, object);
	else if (ft_strncmp(name, "cone", 4) == 0)
		get_cone(json, object);
	else if (ft_strncmp(name, "cylinder", 8) == 0)
		get_cylinder(json, object);
	else if (ft_strncmp(name, "plane", 5) == 0)
		get_plane(json, object);
}
