/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_control_params.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:21:54 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_control.h"

t_rect			ft_get_control_rect(void *ctrl)
{
	t_control	*c;
	t_rect		r;

	c = ctrl;
	if (!c)
	{
		r.w = 0;
		r.h = 0;
		r.x = 0;
		r.y = 0;
		return (r);
	}
	return (c->rect);
}

unsigned int	ft_get_control_color(void *ctrl)
{
	t_control	*c;

	c = ctrl;
	if (!c)
		return (0);
	return (c->bg_color);
}

void			*ft_get_control_param(void *ctrl)
{
	t_control	*c;

	c = ctrl;
	if (!c)
		return (NULL);
	return (c->param);
}

void			*ft_get_control_parent(void *ctrl)
{
	t_control	*c;

	c = ctrl;
	if (!c)
		return (NULL);
	return (c->parent);
}

void			*ft_get_control_pixels(void *ctrl)
{
	t_control	*c;

	c = ctrl;
	if (!c)
		return (NULL);
	return (c->pixels);
}
