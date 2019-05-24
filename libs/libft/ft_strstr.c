/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:25:40 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/24 21:27:39 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	if (!needle[0])
		return ((char*)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (needle[i] && needle[i] == haystack[i])
				++i;
			if (!needle[i])
				return ((char*)haystack);
		}
		++haystack;
	}
	return (0);
}
