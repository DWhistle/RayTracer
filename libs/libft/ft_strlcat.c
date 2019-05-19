/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:24:54 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/24 16:43:31 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ret_size;

	ret_size = 0;
	while (*dst && (size > 0))
	{
		++ret_size;
		++dst;
		--size;
	}
	while (*src && (size > 1))
	{
		*dst++ = *src++;
		++ret_size;
		--size;
	}
	while (*src++)
		++ret_size;
	if (size && *dst)
		*dst = 0;
	return (ret_size);
}
