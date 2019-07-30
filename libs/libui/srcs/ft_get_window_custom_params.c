/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_window_custom_params.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 15:07:05 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_window.h"

void			*ft_get_window_input_param(void *wnd)
{
	t_window	*w;

	w = (t_window*)wnd;
	return (w->input_param);
}

void			*ft_get_window_render_param(void *wnd)
{
	t_window	*w;

	w = (t_window*)wnd;
	return (w->render_param);
}

void			*ft_get_window_window_param(void *wnd)
{
	t_window	*w;

	w = (t_window*)wnd;
	return (w->window_param);
}
