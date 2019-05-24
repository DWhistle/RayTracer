/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:56:13 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/24 19:54:05 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"
#include "SDL2/SDL.h"
#include <OpenGL/gl.h>
#include "objects.h"
#include "ray_render.h"

#define WIN_X   500
#define WIN_Y   500
#define WIN_W   1000
#define WIN_H   600

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
	
	t_sphere circle;
	t_sphere circle2;
	t_plane plane;
	t_plane plane2;
	t_plane plane3;
	t_plane plane4;
	t_plane plane5;
	t_plane plane6;
	t_cylinder cylinder;
	t_scene scene;
	scene.cam = new_vec3(0, 0, 0);
	scene.number_objs = 9;
	scene.objs = malloc(sizeof(t_obj) * scene.number_objs);
	t_light l;
	t_light l1;
	t_light l2;
	l.type = POINT;
	l.point = new_vec3(0150, 0, 1500);
	l.intensity = 0.5;
	l2.type = POINT;
	l2.intensity = 0.5;
	l2.point = new_vec3(-700, 0, 0);
	l1.type = AMBIENT;
	l1.intensity = 0.1;
	circle.r = 100;
	circle.point = new_vec3(0, 0, 2000);
	circle2.r = 200;
	circle2.point = new_vec3(150, 0, 2000);
	plane.norm = new_vec3(0, 0, -1);
	plane.point = new_vec3(0, 0, 3000);
	plane2.norm = vec_norm(new_vec3(-1, 0, 0.2));
	plane2.point = new_vec3(200, 0, 0);
	plane3.norm = vec_norm(new_vec3(1, 0, 0));
	plane3.point = new_vec3(-1000, 0, 0);
	plane4.norm = vec_norm(new_vec3(0, 0, 1));
	plane4.point = new_vec3(0, 0, -1000);
	plane5.norm = vec_norm(new_vec3(0, 1, 0));
	plane5.point = new_vec3(0, -300, 0);
	plane6.norm = vec_norm(new_vec3(0, -1, 0));
	plane6.point = new_vec3(0, 300, 0);
	cylinder.point = new_vec3(0, 0, 2000);;
	cylinder.vec = vec_norm(new_vec3(0, 1, 3));
	cylinder.r = 50;
	scene.objs[0].obj = &circle;
	scene.objs[0].type = CIRCLE;
	scene.objs[0].color = new_vec3(200, 200, 0);
	scene.objs[0].reflection = 0;
	scene.objs[0].ind = 0;
	scene.objs[1].obj = &circle2;
	scene.objs[1].type = CIRCLE;
	scene.objs[1].color = new_vec2(200, 200);
	scene.objs[1].reflection = 0.9;
	scene.objs[1].ind = 1;
	scene.objs[3].obj = &plane;	
	scene.objs[3].type = PLANE;
	scene.objs[3].color = new_vec2(200, 0);
	scene.objs[3].reflection = 0;
	scene.objs[3].ind = 3;
	scene.objs[4].obj = &plane2;
	scene.objs[4].type = PLANE;
	scene.objs[4].color = new_vec2(200, 0);
	scene.objs[4].reflection = 0.8;
	scene.objs[4].ind = 4;
	scene.objs[2].obj = &cylinder;	
	scene.objs[2].type = CYLINDER;
	scene.objs[2].color = new_vec3(0, 0, 255);
	scene.objs[2].reflection = 0;
	scene.objs[2].ind = 2;
	scene.objs[8].obj = &plane3;	
	scene.objs[8].type = PLANE;
	scene.objs[8].color = new_vec2(200, 0);
	scene.objs[8].reflection = 0;
	scene.objs[8].ind = 8;
	scene.objs[7].obj = &plane4;	
	scene.objs[7].type = PLANE;
	scene.objs[7].color = new_vec2(200, 0);
	scene.objs[7].reflection = 0;
	scene.objs[7].ind = 7;
	scene.objs[6].obj = &plane5;	
	scene.objs[6].type = PLANE;
	scene.objs[6].color = new_vec2(200, 0);
	scene.objs[6].reflection = 0;
	scene.objs[6].ind = 6;
	scene.objs[5].obj = &plane6;	
	scene.objs[5].type = PLANE;
	scene.objs[5].color = new_vec2(200, 0);
	scene.objs[5].reflection = 0;
	scene.objs[5].ind = 5;
	scene.number_lights = 3;
	scene.lights = malloc(sizeof(t_light) * scene.number_lights);
	scene.lights[0] = l; 
	scene.lights[1] = l1;
	scene.lights[2] = l2;
	t_accuracy accuracy;
	accuracy.delta = 0.00001;
	accuracy.depth_march = 2000;
	accuracy.depth_pt = 2;
	accuracy.depth_ref = 2;
	accuracy.max_dist = 10000;
	accuracy.rpp = 9;
	scene.ignore = 0;
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0xff, 0xff, 0xff));
	ray_tracing(scene, (int**)&(screen->pixels), accuracy, screen);
    SDL_UpdateWindowSurface(window);
    return (0);
}

int		main_loop(SDL_Window *window)
{
	int			quit;
	SDL_Event	event;

	quit = 0;
	render(window);
	while (!quit)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			if (event.type == SDL_QUIT)
				quit = 1;
		}
		
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

