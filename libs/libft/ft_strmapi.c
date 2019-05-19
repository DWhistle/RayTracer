/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:40:03 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/27 19:01:55 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ret;

	if (!s || !f)
		return (NULL);
	i = 0;
	ret = ft_strnew(ft_strlen(s));
	if (ret)
	{
		while (s[i])
		{
			ret[i] = (unsigned char)f(i, s[i]);
			++i;
		}
		ret[i] = 0;
	}
	return (ret);
}
