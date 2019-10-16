/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:38:40 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/09/28 12:06:34 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_digit(int num, int base)
{
	int		ret;

	ret = 1;
	while (num != 0)
	{
		num = num / base;
		++ret;
	}
	if (base < 0)
		++ret;
	return (ret);
}

char		*ft_itoa_base(long num, int base)
{
	int		count;
	char	*ret;
	int		i;
	char	digit;

	count = ft_count_digit(num, base);
	ret = ft_strnew(count);
	i = 0;
	if (base < 0 && num < 0)
	{
		ret[i++] = '-';
		base = -base;
		num = -num;
	}
	while (count > i)
	{
		digit = num % base;
		if (base > 10 && digit >= 10)
			digit += 'a' - '9' - 1;
		ret[--count] = '0' + digit;
		num = num / base;
	}
	return (ret);
}
