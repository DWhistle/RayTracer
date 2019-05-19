/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:25:56 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/24 16:44:17 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;

	if (!needle[0])
		return ((char*)haystack);
	while (*haystack && len)
	{
		if (*haystack == *needle)
		{
			i = 0;
			while (needle[i] && (needle[i] == haystack[i]) && (len - i > 0))
				++i;
			if (!needle[i])
				return ((char*)haystack);
		}
		++haystack;
		--len;
	}
	return (0);
}
