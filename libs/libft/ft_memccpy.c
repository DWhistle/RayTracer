/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:19:32 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/24 19:07:03 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	while (n)
	{
		*(unsigned char*)dst++ = *(unsigned char*)src++;
		if (*((unsigned char*)src - 1) == (unsigned char)c)
			break ;
		--n;
	}
	if (n)
		return (dst);
	else
		return (NULL);
}
