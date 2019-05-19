/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:25:26 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/28 20:34:34 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*pos;
	size_t	i;

	pos = NULL;
	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			pos = (char*)s + i;
		++i;
	}
	if ((char)c)
		return (pos);
	else
		return ((char*)s + i);
}
