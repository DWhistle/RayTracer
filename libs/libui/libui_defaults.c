/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libui_defaults.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 19:17:14 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/19 20:37:33 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui.h"
#include "libui/ft_window.h"
#include "libui/ft_control.h"

void			ft_window_destroy(void *wnd, size_t size)
{
	if (wnd && size == sizeof(t_window))
	{
		ft_close_window(&wnd);
	}
}

void			ft_libui_quit(t_list *list)
{
	ft_lstdel(&list, ft_window_destroy);
	SDL_Quit();
}

void			ft_control_process(t_list *ctrl, void *param)
{
	t_control	*c;

	if (!ctrl || !ctrl->content)
		return ;
	c = (t_control*)ctrl->content;
	if (c->ontickfunc)
		c->ontickfunc(c, 0, param);
	if (c->children)
		ft_lstiterp(c->children, param, ft_control_process);
}

void			ft_window_process(void *wnd, int num, void *param)
{
	t_window	*w;

	w = (t_window*)wnd;
	if (w->tickfunc)
		w->tickfunc(w, num, param);
	if (w->controls)
		ft_lstiterp(w->controls, param, ft_control_process);
}
