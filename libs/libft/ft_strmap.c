/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:35:34 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/29 04:41:11 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	size_t	i;
	char	*ret;

	i = 0;
	if (!s || !*s || !f)
		return (NULL);
	while (s[i])
		++i;
	ret = ft_strnew(i);
	if (!ret)
		return (NULL);
	i = 0;
	while (s[i])
	{
		ret[i] = f(s[i]);
		++i;
	}
	return (ret);
}
