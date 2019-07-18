/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cursor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 18:57:54 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/28 09:31:29 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL2/SDL.h"
#include "ftui.h"

void			ft_show_cursor(void)
{
	SDL_SetCursor(NULL);
	SDL_ShowCursor(1);
}

void			ft_hide_cursor(void)
{
	SDL_ShowCursor(0);
}

void			ft_set_cursor(void *pixels, t_point size, t_point pos)
{
	SDL_Surface	*surface;
	SDL_Cursor	*cursor;

	surface = SDL_CreateRGBSurfaceWithFormatFrom(pixels, size.x, size.y,
			32, size.x * 4, SDL_PIXELFORMAT_ARGB8888);
	cursor = SDL_CreateColorCursor(surface, pos.x, pos.y);
	SDL_SetCursor(cursor);
}
