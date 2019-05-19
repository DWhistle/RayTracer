/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequ.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:48:28 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/28 20:23:23 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strequ(char const *s1, char const *s2)
{
	size_t	i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	else if (!s2)
		return (1);
	else if (!s1)
		return (-1);
	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (0);
		++i;
	}
	return (s1[i] == s2[i]);
}
