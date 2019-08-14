/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:20:52 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/30 00:16:08 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n)
	{
		if (*(char*)s1 != *(char*)s2)
			return (*(unsigned char*)s1 - *(unsigned char*)s2);
		++s1;
		++s2;
		--n;
	}
	return (0);
}
