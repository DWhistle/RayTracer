/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_logic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:50:18 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/28 13:36:39 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		parse_float(t_parser *json, t_values *value)
{
	double ret;
	double precision;

	precision = 0.1;
	ret = 0.0;
	while (json->f[json->i] && !ft_isdigit(json->f[json->i])
	&& json->f[json->i] != '-')
		json->i++;
	ret = ft_atoi(json->f + json->i);
	precision = (json->f[json->i] == '-') ? -precision : precision;
	while (json->f[json->i] && json->f[json->i] != '.')
		json->i++;
	while (json->f[++json->i] && ft_isdigit(json->f[json->i]))
	{
		ret += (json->f[json->i] - 48) * precision;
		precision *= 0.1;
	}
	(*value).float_value = ret;
	return (1);
}

int		parse_int(t_parser *json, t_values *value)
{
	(*value).int_value = ft_atoi(json->f + json->i);
	return (1);
}

int		parse_key(t_parser *json, char **key)
{
	int temp;

	temp = 0;
	while (json->f[json->i])
	{
		if (json->f[json->i] == '"')
		{
			temp = json->i;
			while (json->f[json->i])
			{
				json->i++;
				if (json->f[json->i] == '"' && !escape(json))
				{
					*key = ft_strsub(json->f,\
							temp + 1, json->i - temp - 1);
					return (1);
				}
			}
		}
		json->i++;
	}
	return (0);
}

int		parse_value(t_parser *json, t_values *value, int **type, int i)
{
	while (json->f[json->i])
	{
		if (json->f[json->i] == '{')
		{
			((*type)[i]) = JSON;
			value[i].json_value = create_json_obj();
			return (make_json(json, value[i].json_value));
		}
		else if (json->f[json->i] == '"' && ((*type)[i] = STRING))
			return (parse_key(json, &(value[i].string_value)));
		else if (ft_isdigit(json->f[json->i]) || json->f[json->i] == '-')
		{
			if (is_float(json) && ((*type)[i] = FLOAT))
				return (parse_float(json, &(value[i])));
			else if (((*type)[i] = INT))
				return (parse_int(json, &(value[i])));
		}
		json->i++;
	}
	return (1);
}
