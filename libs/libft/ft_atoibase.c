/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoibase.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 19:14:17 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/30 00:16:08 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strtolower(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		++i;
	}
	return (str);
}

unsigned long	ft_atoibase(char *nbr, char base)
{
	int				i;
	unsigned long	ret;

	if (!nbr)
		return (0);
	else
		++nbr;
	ft_strtolower(nbr);
	while (*nbr == ' ' || *nbr == '0')
		++nbr;
	i = 0;
	ret = 0;
	while (nbr[i])
	{
		if (ft_isdigit(nbr[i]))
			ret = base * ret + (nbr[i] - '0');
		else if ((ft_isalpha(nbr[i]) && (base > nbr[i] - 'a' + 10)))
			ret = base * ret + (nbr[i] - 'a' + 10);
		else
			return (ret);
		++i;
	}
	return (ret);
}
