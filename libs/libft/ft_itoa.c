/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:12:47 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/24 23:02:37 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_getzero(void)
{
	char	*zero;

	zero = ft_strnew(1);
	if (zero)
		zero[0] = '0';
	return (zero);
}

static int	ft_getsize(int n)
{
	int	sz;

	sz = 0;
	if (n < 0)
		sz++;
	while (n != 0)
	{
		sz++;
		n /= 10;
	}
	return (sz);
}

char		*ft_itoa(int n)
{
	int		pos;
	char	*ansinum;
	int		negative;

	negative = 1;
	if (n == 0)
		return (ft_getzero());
	pos = ft_getsize(n);
	ansinum = ft_strnew(pos);
	if (!ansinum)
		return (NULL);
	ansinum[pos--] = 0;
	if (n < 0)
		negative = -1;
	while (n != 0)
	{
		ansinum[pos] = '0' + (n % 10) * negative;
		n /= 10;
		--pos;
	}
	if (negative < 0)
		ansinum[pos] = '-';
	return (ansinum);
}
