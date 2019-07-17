/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 10:53:20 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/15 10:22:40 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_WINDOW_H
# define FT_WINDOW_H
# include "SDL2/SDL.h"
# include "libft.h"
# include "ftui.h"

# define ERR_POINTER	-1

typedef	struct			s_window {
	uint32_t			id;
	SDL_Window			*ptr_wnd;
	SDL_Renderer		*ptr_rndr;
	SDL_Surface			*sdl_surface;
	SDL_Texture			*sdl_texture;
	int					width;
	int					height;
	int					pos_x;
	int					pos_y;
	unsigned int		color;
	char const			*title;
	int					quit;
	int					last_tick;
	int					is_active;
	char				*keys;
	void				*input_param;
	void				*render_param;
	void				*window_param;
	t_list				*controls;
	t_windowevent_func	keypress;
	t_windowevent_func	mousemove;
	t_windowevent_func	mousedown;
	t_windowevent_func	mouseup;
	t_windowevent_func	beforeclose;
	t_windowevent_func	defaultfunc;
	t_windowevent_func	windowfunc;
	t_windowevent_func	renderfunc;
	t_windowevent_func	tickfunc;
}						t_window;

#endif
