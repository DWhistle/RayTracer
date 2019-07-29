/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 20:21:53 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui.h"
#include "ft_window.h"
#include "ft_control.h"

/*
** функция отрисовки дочерних елементов контрола cntrl
** с уже отрисованным самим элементом, внутрь текстуры render
*/

void			ft_redraw_children(t_control *cntrl, SDL_Texture *render)
{
	SDL_Texture		*prev;

	prev = SDL_GetRenderTarget(cntrl->parent->ptr_rndr);
	cntrl->texture = SDL_CreateTexture(cntrl->parent->ptr_rndr,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_TARGET,
		cntrl->rect.w, cntrl->rect.h);
	SDL_SetRenderTarget(cntrl->parent->ptr_rndr, cntrl->texture);
	SDL_SetRenderDrawBlendMode(cntrl->parent->ptr_rndr, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(cntrl->parent->ptr_rndr, render, NULL, NULL);
	if (cntrl->children)
		ft_lstiter(cntrl->children, ft_redraw);
	SDL_SetRenderTarget(cntrl->parent->ptr_rndr, prev);
	SDL_SetRenderDrawBlendMode(cntrl->parent->ptr_rndr, SDL_BLENDMODE_BLEND);
	SDL_RenderCopy(cntrl->parent->ptr_rndr, cntrl->texture, NULL,
			(SDL_Rect*)&cntrl->rect);
	SDL_DestroyTexture(cntrl->texture);
	SDL_DestroyTexture(render);
}

void			ft_redraw(t_list *lst)
{
	t_control		*cntrl;
	SDL_Texture		*render;
	int				pitch;
	void			*pxls;

	if (!lst)
		return ;
	cntrl = (t_control *)(lst->content);
	if (cntrl->rect.w * cntrl->rect.h > 0)
	{
		render = SDL_CreateTexture(cntrl->parent->ptr_rndr,
				SDL_PIXELFORMAT_ARGB8888,
				SDL_TEXTUREACCESS_STREAMING,
				cntrl->rect.w, cntrl->rect.h);
		pxls = cntrl->pixels;
		cntrl->pixels = NULL;
		SDL_LockTexture(render, NULL, (void**)&(cntrl->pixels), &pitch);
		ft_add_textures(
		cntrl->pixels, pxls, cntrl->rect.w * cntrl->rect.h);
		if (cntrl->ondraw)
			cntrl->ondraw(cntrl, pitch, cntrl->pixels);
		SDL_UnlockTexture(render);
		cntrl->pixels = pxls;
		ft_redraw_children(cntrl, render);
	}
}

void			ft_window_redraw(void *wnd, int num, void *param)
{
	t_window	*w;

	w = (t_window*)wnd;
	SDL_SetRenderDrawColor(w->ptr_rndr
			, (w->color >> 24u) & 0xffu
			, (w->color >> 16u) & 0xffu
			, (w->color >> 8u) & 0xffu
			, (w->color) & 0xffu);
	SDL_SetRenderDrawBlendMode(w->ptr_rndr, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(w->ptr_rndr);
	if (w->renderfunc)
		w->renderfunc(w, num, param);
	w->sdl_texture = SDL_CreateTextureFromSurface(w->ptr_rndr,
					w->sdl_surface);
	if (w->controls)
	{
		ft_lstiter(w->controls, ft_redraw);
	}
	SDL_RenderCopy(w->ptr_rndr, w->sdl_texture, NULL, NULL);
	SDL_RenderPresent(w->ptr_rndr);
	SDL_DestroyTexture(w->sdl_texture);
}
