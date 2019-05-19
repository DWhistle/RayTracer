/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:56:13 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/19 15:02:23 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "incs/libft.h"
#include "SDL2/SDL.h"
#include <OpenGL/gl.h>

#define WIN_X   1024
#define WIN_Y   768
#define WIN_W   1024
#define WIN_H   768

int    print_error(int errnum)
{
    if (errnum == 1)
        ft_putendl("Error! SDL Init error");
    else if (errnum == 2)
        ft_putendl("Error! Create window error");
    return (0);
}

int		in_circle(SDL_Rect rect, int x, int y)
{
	int 	r_x;
	int 	r_y;

	r_x = rect.w / 2;
	r_y = rect.h / 2;
	return ((x - rect.x - r_x) * (x - rect.x - r_x) / (double)(r_x * r_x) +
			(y - rect.y - r_y) * (y - rect.y - r_y) / (double)(r_y * r_y) <= 1.0);
}

void	draw_circle(SDL_Surface *screen, SDL_Rect rect, int color)
{
	int		x0;
	int		y0;
	int		*map;
	int 	i;
	int 	j;

	map = (int*)screen->pixels;
	x0 = rect.x;
	y0 = rect.y;
	i = 0;
	while (i < rect.h)
	{
		j =  0;
		while (j < rect.w)
		{
			if (in_circle(rect, x0 + j, y0 + i))
				map[(y0 + i) * screen->w + (x0 + j)] = color;
			++j;
		}
		++i;
	}
}

void	draw_rect(SDL_Surface *screen, SDL_Rect rect, int color)
{
	int		x0;
	int		y0;
	int		*map;
	int 	i;
	int 	j;

	map = (int*)screen->pixels;
	x0 = rect.x;
	y0 = rect.y;
	i = 0;
	while (i < rect.h)
	{
		j =  0;
		while (j < rect.w)
		{
			map[(y0 + i) * screen->w + (x0 + j)] = color;
			++j;
		}
		++i;
	}
}

int     render(SDL_Window *window)
{
	SDL_Surface		*screen;
	SDL_Rect		rect;

	rect.x = 100;
	rect.y = 100;
	rect.w = 100;
	rect.h = 100;
	screen = SDL_GetWindowSurface(window);

    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));
    draw_rect(screen, rect, 0xff0000);
	draw_circle(screen, rect, 0x90);
    SDL_UpdateWindowSurface(window);
    return (0);
}

int		main_loop(SDL_Window *window)
{
	int			quit;
	SDL_Event	event;

	quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = 1;
		}
		render(window);
	}
	return (0);
}

int     main(int argc, char **argv)
{
    SDL_Window      *window;

    (void)argc;
    (void)argv;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return (print_error(1));
    else
        window = SDL_CreateWindow("Test", WIN_X, WIN_Y, WIN_W, WIN_H,
        		SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (window == NULL)
        return (print_error(2));
    else
    {
        render(window);
    }
    main_loop(window);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return (0);
}

