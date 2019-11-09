/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 10:54:48 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/11/09 16:07:10 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL2/SDL.h"
#include "libft.h"
#include "ftui.h"
#include "ft_window.h"

void		*ft_create_new_window(void)
{
	t_window	*wnd;

	wnd = (t_window*)ft_memalloc(sizeof(t_window));
	wnd->quit = 0;
	ft_set_window_color((void*)wnd, 0);
	wnd->keys = ft_memalloc(sizeof(char) * SDL_NUM_SCANCODES);
	wnd->controls = NULL;
	wnd->ptr_wnd = NULL;
	wnd->ptr_rndr = NULL;
	wnd->sdl_texture = NULL;
	wnd->keypress = NULL;
	wnd->mousemove = NULL;
	wnd->beforeclose = NULL;
	wnd->windowfunc = NULL;
	wnd->renderfunc = NULL;
	wnd->tickfunc = NULL;
	return (wnd);
}

void		ft_close_window(void **wnd)
{
	if (!wnd || !*wnd)
		return ;
	if (((t_window*)*wnd)->beforeclose)
		((t_window*)*wnd)->beforeclose(wnd, 0, NULL);
	if (((t_window*)*wnd)->sdl_surface)
		SDL_FreeSurface(((t_window*)*wnd)->sdl_surface);
	if (((t_window*)*wnd)->sdl_texture)
		SDL_DestroyTexture(((t_window*)*wnd)->sdl_texture);
	if (((t_window*)*wnd)->ptr_rndr)
		SDL_DestroyRenderer(((t_window*)*wnd)->ptr_rndr);
	if (((t_window*)*wnd)->ptr_wnd)
		SDL_DestroyWindow(((t_window*)*wnd)->ptr_wnd);
	((t_window*)*wnd)->sdl_surface = NULL;
	((t_window*)*wnd)->sdl_texture = NULL;
	((t_window*)*wnd)->ptr_rndr = NULL;
	((t_window*)*wnd)->ptr_wnd = NULL;
	while (((t_window*)*wnd)->controls)
	{
		ft_delete_control(&(((t_window*)*wnd)->controls->content));
		((t_window*)*wnd)->controls = ((t_window*)*wnd)->controls->next;
	}
	ft_memset(*wnd, 0, sizeof(t_window));
	ft_memdel((void**)wnd);
}

int			ft_show_window(void *wnd)
{
	t_window	*w;

	if (!wnd)
		return (ERR_POINTER);
	w = (t_window*)wnd;
	w->ptr_wnd = SDL_CreateWindow(
			w->title,
			w->pos_x, w->pos_y,
			w->width, w->height,
			SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	w->id = SDL_GetWindowID(w->ptr_wnd);
	if (!(w->ptr_wnd))
		return (ERR_POINTER);
	w->ptr_rndr = SDL_CreateRenderer(w->ptr_wnd, -1,
			SDL_RENDERER_ACCELERATED);
	if (!(w->ptr_rndr))
		return (ERR_POINTER);
	w->sdl_surface = SDL_CreateRGBSurface(0, w->width, w->height,
			32, 0x00ff0000u, 0x0000ff00, 0x000000ff, 0xff000000);
	if (!(w->sdl_surface))
		return (ERR_POINTER);
	SDL_ShowWindow(w->ptr_wnd);
	return (0);
}

int			*ft_get_window_pixels(void *wnd, t_rect *rect)
{
	t_window	*w;

	w = (t_window*)wnd;
	if (!wnd)
		return (NULL);
	if (rect)
	{
		rect->w = w->sdl_surface->w;
		rect->h = w->sdl_surface->h;
		rect->x = w->pos_x;
		rect->y = w->pos_y;
	}
	return (w->sdl_surface->pixels);
}
