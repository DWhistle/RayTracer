/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 21:24:04 by hgreenfe          #+#    #+#             */
/*   Updated: 2018/11/25 01:48:58 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int		negative;

	negative = 1;
	if (n < 0)
	{
		negative = -1;
		ft_putchar_fd('-', fd);
	}
	if (n < 10 && n > -10)
	{
		ft_putchar_fd('0' + n * negative, fd);
		return ;
	}
	ft_putnbr_fd((n / 10) * negative, fd);
	ft_putchar_fd((n % 10) * negative + '0', fd);
}
