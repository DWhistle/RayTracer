/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 22:33:24 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/24 19:07:03 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	void	*start;

	start = b;
	c = (c & 0xff) | ((c & 0xff) << 8) |
		((c & 0xff) << 16) | ((c & 0xff) << 24);
	while (len > sizeof(int))
	{
		*(int*)b = c;
		b = ((char*)b) + sizeof(int);
		len -= sizeof(int);
	}
	while (len-- > 0)
	{
		*(char*)b++ = (unsigned char)(c & 0xff);
	}
	return (start);
}
