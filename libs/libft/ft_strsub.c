/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:55:08 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/30 00:16:08 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*ret;

	if (!s)
		return (NULL);
	ret = (char*)malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (i < len)
	{
		if (s[start + i])
			ret[i] = s[start + i];
		else
		{
			free(ret);
			return (NULL);
		}
		++i;
	}
	ret[i] = 0;
	return (ret);
}
