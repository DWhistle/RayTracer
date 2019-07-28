/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:53:17 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/25 20:50:28 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	is_float(t_parser *json)
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

int	escape(t_parser *json)
{
	if (json->i > 0)
		return (json->f[json->i - 1] == '\\');
	return (0);
}
