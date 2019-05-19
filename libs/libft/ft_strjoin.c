/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:05:20 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/12/01 02:58:34 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	char	*start;
	size_t	len1;
	size_t	len2;
	size_t	i;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	ret = (char*)ft_memalloc(sizeof(char) * (len1 + len2 + 1));
	if (!ret)
		return (NULL);
	start = ret;
	while (*s1)
		*ret++ = *s1++;
	i = 0;
	while (i < len2)
	{
		ret[i] = s2[i];
		++i;
	}
	ret[i] = 0;
	return (start);
}
