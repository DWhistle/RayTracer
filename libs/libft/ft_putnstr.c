/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:14:14 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/27 16:45:06 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

static char	*ft_newchars(char c, size_t len)
{
	char	*str;

	str = malloc(len + 1);
	ft_memset(str, c, len);
	str[len] = 0;
	return (str);
}

void		ft_putnstr(char const *s, size_t len)
{
	size_t	curernt_len;
	char	*fills;

	if (s)
	{
		curernt_len = ft_strlen(s);
		if (len <= curernt_len)
		{
			write(1, s, len);
		}
		else if (len > curernt_len)
		{
			fills = ft_newchars(' ', len - curernt_len);
			write(1, s, curernt_len);
			write(1, fills, len - curernt_len);
		}
	}
}
