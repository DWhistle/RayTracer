/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:53:17 by bturcott          #+#    #+#             */
/*   Updated: 2019/10/13 21:06:30 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	free_json_obj(t_json *obj)
{
	int i;

	i = 0;
	while (obj->key[i] != 0 && i < MAX_FIELDS)
	{
		if (obj->type[i] == JSON)
		{
			free_json_obj((t_json *)(obj->value[i].json_value));
		}
		else if (obj->type[i] == STRING)
		{
			free(&obj->value[i].string_value);
		}
		free(obj->key[i]);
		i++;
	}
}

int		is_float(t_parser *json)
{
	int i;

	i = json->i;
	while (json->f[i] && json->f[i] != ',')
	{
		if (json->f[i] == '.')
			return (1);
		i++;
	}
	return (0);
}

int		escape(t_parser *json)
{
	if (json->i > 0)
		return (json->f[json->i - 1] == '\\');
	return (0);
}
