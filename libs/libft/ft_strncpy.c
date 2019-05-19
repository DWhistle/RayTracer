/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 22:16:16 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/24 20:35:59 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t len)
{
	char	*start;

	start = dst;
	while (len && *src)
	{
		*dst++ = *src++;
		--len;
	}
	while (len--)
		*dst++ = 0;
	return (start);
}
