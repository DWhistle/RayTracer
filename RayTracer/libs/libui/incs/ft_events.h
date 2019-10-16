/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_events.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:13:31 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_EVENTS_H
# define FT_EVENTS_H
# include "ft_window.h"
# include "ft_control.h"

# define DEFAULT_TICKS	1000

typedef	SDL_Event	t_event;

int					ft_window_main(void *wnd, t_event *event);
int					ft_events_main(void *wnd, t_event *event);
int					ft_input_main(void *wnd, t_event *event);
void				ft_window_mouse_event(t_window *wnd, t_event *event);
void				ft_controllist_mouse_event(t_list *controls, void *event);
#endif
