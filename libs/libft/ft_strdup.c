/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 20:22:37 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/24 22:58:54 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	char	*begin;

	ret = ft_strnew(ft_strlen(s1));
	if (!ret)
		return (NULL);
	begin = ret;
	while (*s1)
		*ret++ = *s1++;
	*ret = 0;
	return (begin);
}
