/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:19:57 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/24 23:20:56 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	void	*origin;
	size_t	vec;

	origin = dst;
	vec = 1;
	if (src == dst)
		return (dst);
	if (src < dst)
	{
		vec = -1;
		dst += len - 1;
		src += len - 1;
	}
	while (len)
	{
		(*(unsigned char*)dst) = (*(unsigned char*)src);
		dst += vec;
		src += vec;
		--len;
	}
	return (origin);
}
