/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 20:39:35 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/29 20:41:13 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		ft_word_count(const char *s, char c)
{
	int		i;
	int		new_word;
	int		count;

	i = 0;
	new_word = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
		{
			if (new_word)
				count++;
			new_word = 0;
		}
		if (s[i] != c && !new_word)
			new_word = 1;
		++i;
	}
	return (count + new_word);
}

static char		*ft_new_word(char const *src, int from, int len)
{
	char	*str;
	char	*ret;

	str = ft_strnew(len);
	if (!str)
		return (NULL);
	ret = ft_strncpy(str, src + from, len);
	if (ret)
		ret[len] = 0;
	if (ret && ret[0])
		return (ret);
	else
		return (NULL);
}

char			**ft_strsplit(char const *s, char c)
{
	int		i;
	int		wc;
	int		new_w;
	char	**arr_result;

	if (!s)
		return (NULL);
	wc = ft_word_count(s, c);
	if (!(arr_result = (char**)malloc(sizeof(char*) * (wc + 1))))
		return (NULL);
	arr_result[wc] = 0;
	i = -1;
	wc = 0;
	new_w = -1;
	while (s[++i])
	{
		if ((s[i] == c) && (new_w >= 0))
			arr_result[wc++] = ft_new_word(s, new_w, i - new_w);
		if (s[i] == c)
			new_w = -1;
		if (s[i] != c && (new_w < 0))
			new_w = i;
	}
	arr_result[wc] = new_w >= 0 ? ft_new_word(s, new_w, i - new_w) : 0;
	return (arr_result);
}
