/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:25:18 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/26 23:24:22 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	int		i;
	int		len;
	char	*ret;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		++i;
	len = ft_strlen(s) - 1;
	while (i < len && (s[len] == ' ' || s[len] == '\t' || s[len] == '\n'))
		--len;
	ret = ft_strsub(s, i, len - i + 1);
	if (!ret)
		return (NULL);
	else
		return (ret);
}
