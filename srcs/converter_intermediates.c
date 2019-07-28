/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_intermediates.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:29:11 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/28 14:56:47 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	get_tor(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_tor;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_hexagonal_prism(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_hexagonal_prism;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_triangular_prism(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_triangular_prism;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_capsule(t_json *json, t_obj *object)
{
	object->type = SPHERE;
	object->len = len_capsule;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param").json_value);
}

void	get_intermediates(t_json *json, char *name, t_obj *object)
{
	if (ft_strncmp(name, "tor", 3) == 0)
		get_tor(json, object);
	else if (ft_strncmp(name, "hexagonal_prism", 15) == 0)
		get_hexagonal_prism(json, object);
	else if (ft_strncmp(name, "triangular_prism", 16) == 0)
		get_triangular_prism(json, object);
	else if (ft_strncmp(name, "capsule", 7) == 0)
		get_capsule(json, object);
}
