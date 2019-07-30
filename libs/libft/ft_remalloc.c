/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 19:09:53 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/30 00:16:08 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_remalloc(void *addr, size_t old_size, size_t new_size)
{
	void	*new;
	void	*old;

	old = addr;
	if (!addr || !new_size)
		return (NULL);
	new = malloc(new_size);
	if (!new)
		return (NULL);
	while (old_size--)
	{
		*(unsigned char*)new++ = *(unsigned char*)addr++;
	}
	ft_bzero(new, new_size - old_size);
	ft_memdel(old);
	return (new);
}
