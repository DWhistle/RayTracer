/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_window_custom_params.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:07:01 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_window.h"

void			ft_set_window_input_param(void *wnd, void *param)
{
	t_window	*w;

	w = (t_window*)wnd;
	w->input_param = param;
}

void			ft_set_window_render_param(void *wnd, void *param)
{
	t_window	*w;

	w = (t_window*)wnd;
	w->render_param = param;
}

void			ft_set_window_window_param(void *wnd, void *param)
{
	t_window	*w;

	w = (t_window*)wnd;
	w->window_param = param;
}
