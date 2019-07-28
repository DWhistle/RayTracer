/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/28 14:38:48 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/28 16:13:48 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int		check_names_light(char *name)
{
	return (!ft_strncmp(name, "light", 4));
}

int		get_names_obj(t_json *j, char ***names, int (*check_names)())
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
