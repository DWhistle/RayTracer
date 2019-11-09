/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_func.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:02:51 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/09/26 19:50:11 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL2/SDL.h"
#include "ftui.h"
#include "libft.h"

int		print_error(int errnum)
{
	if (errnum == 1)
		ft_putendl("Error! SDL Init error");
	else if (errnum == 2)
		ft_putendl("Error! Create window error");
	return (0);
}

void	ft_printmem(void *pxls, int w, int h)
{
	SDL_Surface	*surface;

	surface = SDL_CreateRGBSurfaceFrom(pxls, w, h, 32, 8,
				0xff, 0xff00, 0xff0000, 0xff000000);
	SDL_SaveBMP(surface, "screenshot.bmp");
}
