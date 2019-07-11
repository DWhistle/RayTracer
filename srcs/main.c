/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:56:13 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/11 21:28:03 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"	
#include "SDL2/SDL.h"
#include <OpenGL/gl.h>
#include "objects.h"
#include "ray_render.h"
#include "ft_opencl_func.h"
#include "libft.h"
#include <stdio.h>
#include "parser.h"

#define WIN_X   500
#define WIN_Y   500
#define WIN_W   600
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

t_obj2	*fc(t_obj *objs, double n)
{
	t_obj2	*obj;
	int		counter;

	obj = ft_memalloc(sizeof(t_obj2) * n);
	counter = n;
	while(counter--)
	{
		obj[counter].color = objs[counter].color;
		obj[counter].ind = objs[counter].ind;
		obj[counter].reflection = objs[counter].reflection;	
		obj[counter].type = objs[counter].type;
		if (objs[counter].type == SPHERE)
		{
			obj[counter].point = ((t_sphere*)objs[counter].obj)->point;
			obj[counter].r = ((t_sphere*)objs[counter].obj)->r;
		}
		if (objs[counter].type == CYLINDER)
		{
			obj[counter].point = ((t_cylinder*)objs[counter].obj)->point;
			obj[counter].r = ((t_cylinder*)objs[counter].obj)->r;
			obj[counter].vec = ((t_cylinder*)objs[counter].obj)->vec;
		}
		if (objs[counter].type == PLANE)
		{
			obj[counter].point = ((t_plane*)objs[counter].obj)->point;	
			obj[counter].vec = ((t_plane*)objs[counter].obj)->norm;
		}
	}
	return(obj);
}

void	render_cl(t_scene scene, int **pixels, t_accuracy accuracy, SDL_Surface *screen)
{
	t_opencl	*ocl;
	t_obj2		*obj;
	cl_mem		mem;
	
	init_cl(&ocl);
	accuracy.rpp = (int)sqrt((float)accuracy.rpp);
	if(!compile_cl_by_name(ocl, "render"))
		printf("%s\n", "ты даун");
	add_parameter(ocl, 1, &accuracy, sizeof(t_accuracy));
	add_parameter(ocl, 1, &scene, sizeof(t_scene));
	add_parameter(ocl, scene.number_lights, scene.lights, sizeof(t_light));
	obj = fc(scene.objs, scene.number_objs);
	add_parameter(ocl, scene.number_objs, obj, sizeof(t_obj2));
	mem = add_parameter_i(ocl, screen->h * screen->w, *pixels);
	add_parameter_i(ocl, 1, &screen->w);
	add_parameter_i(ocl, 1, &screen->h);
	run_queue(ocl, screen->w * screen->h);
	get_parameter_i(ocl, screen->h * screen->w, mem, *pixels);
	free(obj);
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
	t_plane plane7;
	t_cylinder cylinder;
	t_cone	tor;
	t_scene scene;
	scene.cam = new_vec3(0, 0, 0);
	scene.number_objs = 9;
	scene.objs = malloc(sizeof(t_obj) * scene.number_objs);
	t_light l;
	t_light l1;
	t_light l2;
	l.type = AMBIENT;
	l.intensity = 0.0;
	l2.type = POINT;
	l2.intensity = 0.4;
	l2.point = new_vec3(-100, 0, 500);
	l2.r = 10;
	l1.type = POINT;
	l1.intensity = 0.4;
	l1.point = new_vec3(100, 0, 200);
	l1.r = 45;
	circle.r = 60;
	circle.point = new_vec3(0, 0, 3000);
	circle2.r = 100;
	circle2.point = new_vec3(0, 0, 100);
	plane.norm = vec_norm(new_vec3(0, -1, -1));
	plane.point = new_vec3(0, 0, 700);
	plane2.norm = vec_norm(new_vec3(-1, -1, 0));
	plane2.point = new_vec3(210, 0, 0);
	plane3.norm = vec_norm(new_vec3(1, -0.5, 0));
	plane3.point = new_vec3(-210, 0, 0);
	plane4.norm = vec_norm(new_vec3(0, 0, 1));
	plane4.point = new_vec3(0, 0, -5);
	plane5.norm = vec_norm(new_vec3(0, 1, 0));
	plane5.point = new_vec3(0, -210, 0);
	plane6.norm = vec_norm(new_vec3(0, -1, 0));
	plane6.point = new_vec3(0, 210, 0);
	plane7.norm = vec_norm(new_vec3(0, 1, 1));
	plane7.point = new_vec3(0, 0, 200);
	cylinder.point = new_vec3(0, 0, 400);
	cylinder.vec = vec_norm(new_vec3(2, 0, 1));
	cylinder.r = 30;
	tor.vec = vec_norm(new_vec3(2, 0, 1));
	tor.angle = 0;
	tor.point = new_vec3(200, 0, 200);
	scene.objs[0].obj = &circle;
	scene.objs[0].type = SPHERE;
	scene.objs[0].color = new_vec3(180, 120, 256);
	scene.objs[0].reflection = 0;
	scene.objs[0].ind = 0;
	scene.objs[0].refraction = 0;
	scene.objs[1].obj = &tor;
	scene.objs[1].type = CONE;
	scene.objs[1].color = new_vec3(0, 0, 255);
	scene.objs[1].reflection = 0.9;
	scene.objs[1].ind = 1;
	scene.objs[1].refraction = 0;
	scene.objs[3].obj = &plane;	
	scene.objs[3].type = PLANE;
	scene.objs[3].color = new_vec2(80, 80);
	scene.objs[3].reflection = 0;
	scene.objs[3].ind = 3;
	scene.objs[3].refraction = 0.0;
	scene.objs[4].obj = &plane2;
	scene.objs[4].type = PLANE;
	scene.objs[4].color = new_vec3(20, 300, 0);
	scene.objs[4].reflection = 0;
	scene.objs[4].ind = 4;
	scene.objs[4].refraction = 0;
	scene.objs[2].obj = &cylinder;	
	scene.objs[2].type = CYLINDER;
	scene.objs[2].color = new_vec3(200, 0, 0);
	scene.objs[2].reflection = 0;
	scene.objs[2].ind = 2;
	scene.objs[2].refraction = 0.0;
	scene.objs[8].obj = &plane3;	
	scene.objs[8].type = PLANE;
	scene.objs[8].color = new_vec2(0, 200);
	scene.objs[8].reflection = 0;
	scene.objs[8].ind = 8;
	scene.objs[8].refraction = 0;
	scene.objs[7].obj = &plane4;	
	scene.objs[7].type = PLANE;
	scene.objs[7].color = new_vec2(200, 0);	
	scene.objs[7].reflection = 0;
	scene.objs[7].ind = 7;
	scene.objs[7].refraction = 0;
	scene.objs[6].obj = &plane5;	
	scene.objs[6].type = PLANE;
	scene.objs[6].color = new_vec2(100, 200);
	scene.objs[6].reflection = 0;
	scene.objs[6].ind = 6;
	scene.objs[6].refraction = 0;
	scene.objs[5].obj = &plane6;	
	scene.objs[5].type = PLANE;
	scene.objs[5].color = new_vec2(200, 100);
	scene.objs[5].reflection = 0;
	scene.objs[5].ind = 5;
	scene.objs[5].refraction = 0;
	scene.number_lights = 3;
	scene.lights = malloc(sizeof(t_light) * scene.number_lights);
	scene.lights[0] = l; 
	scene.lights[1] = l1;
	scene.lights[2] = l2;
	t_accuracy accuracy;	
	accuracy.delta = 0.01;
	accuracy.depth_march = 200;
	accuracy.depth_pt = 1;
	accuracy.depth_ref = 0;
	accuracy.max_dist = 10000;
	accuracy.rpp = 1;
	scene.ignore = 0;
	scene.color = ft_memalloc(sizeof(t_vec) * screen->h * screen->w);
	srand(time(NULL));
	//render_cl(scene, (int**)&(screen->pixels), accuracy, screen);
	int i = 1;
	while (i--)
	{
		ray_tracing(scene, (int**)&(screen->pixels), accuracy, screen);
		accuracy.depth_pt++;
	}
	SDL_UpdateWindowSurface(window);
	free(scene.objs);
	free(scene.lights);
    return (0);
}

int		main_loop(SDL_Window *window)
{
	int			quit;
	SDL_Event	event;

	quit = 0;
	window = 0;
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

