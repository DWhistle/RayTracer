/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_control_params.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 16:30:28 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_control.h"

void			ft_set_control_rect(void *ctrl, t_rect rect)
{
	t_control	*c;

	c = ctrl;
	if (!c)
		return ;
	c->rect.w = rect.w;
	c->rect.h = rect.h;
	c->rect.x = rect.x;
	c->rect.y = rect.y;
}

void			ft_set_control_color(void *ctrl, unsigned int bg_color)
{
	t_control	*c;

	c = ctrl;
	if (!c)
		return ;
	c->bg_color = bg_color;
}

void			ft_set_control_param(void *ctrl, void *param)
{
	t_control	*c;

	c = ctrl;
	if (!c)
		return ;
	c->param = param;
}
