/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:58:56 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui.h"
#include "ft_window.h"
#include "ft_events.h"

int				add_window(void **libui, t_rect rect,
		int color, char const *title)
{
	t_list		*elem;
	t_window	*wnd;

	wnd = ft_create_new_window();
	ft_set_window_title(wnd, title);
	ft_set_window_position(wnd, rect.x, rect.y);
	ft_set_window_size(wnd, rect.w, rect.h);
	ft_set_window_color(wnd, color);
	if (ft_show_window(wnd))
	{
		ft_putendl(SDL_GetError());
		exit(0);
	}
	elem = ft_lstnew(wnd, sizeof(t_window));
	ft_lstadd((t_list**)libui, elem);
	return (0);
}

void			*ft_libui_init(void)
{
	t_list		*list;

	if (SDL_Init(SDL_INIT_VIDEO))
		ft_putendl(SDL_GetError());
	list = NULL;
	return (list);
}

int				ft_process(t_list *list)
{
	t_list			*next;
	t_window		*wnd;
	int				ticks;

	if (!list || !list->content)
		return (1);
	ticks = SDL_GetTicks();
	next = list;
	while (next)
	{
		wnd = ((t_window*)next->content);
		if (wnd && !(wnd->quit))
		{
			ft_window_redraw(wnd, ticks, wnd->render_param);
			if (ticks - wnd->last_tick > DEFAULT_TICKS)
			{
				ft_window_process(wnd, ticks, NULL);
				wnd->last_tick = ticks;
			}
		}
		next = next->next;
	}
	return (0);
}

unsigned int	ft_correct_quit(void *libui)
{
	t_list	*list;

	list = libui;
	if (!list || !list->content)
		return (1);
	if (((t_window*)list->content)->quit)
	{
		ft_close_window(&(list->content));
		return (1);
	}
	else
		return (0);
}

void			ft_mainloop(void *list)
{
	unsigned int	quit;
	t_list			*next;
	SDL_Event		event;

	quit = 0;
	while (!quit)
	{
		if (SDL_PollEvent(&event))
		{
			next = list;
			quit = 1;
			while (next)
			{
				if (next->content && !(((t_window*)next->content)->quit))
				{
					ft_window_main(((t_window*)next->content), &event);
					ft_events_main(((t_window*)next->content), &event);
					ft_input_main(((t_window*)next->content), &event);
					quit &= ft_correct_quit(next);
				}
				next = next->next;
			}
		}
		ft_process(list);
	}
}
