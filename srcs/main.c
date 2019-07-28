/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:56:13 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/25 14:26:45 by kmeera-r         ###   ########.fr       */
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
#include "ftui.h"

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

int     render(void *window, t_scene *scene)
{
	t_rect				screen;
	int					*pixels;

	pixels = ft_get_window_pixels(window, &screen);
	srand(time(NULL));
	scene->accuracy.depth_pt++;
	ray_tracing(*scene, (int**)&(pixels), scene->accuracy, &screen);
    return (0);
}



void	ft_key_func(void *wnd, int n, void *param)
{
	if (n == 21) // клавиша r
	{
		param = ft_get_window_input_param(wnd);
		render(wnd, (t_scene*)param);
	}
	if (n == FTUI_KEY_ESCAPE)
	{
		ft_set_window_quit(wnd, 1);
	}
}

void	ft_render(void *wnd, int n, void* param)
{
	t_point size;

	size = ft_get_window_size(wnd);
	(void)wnd;
	(void)n;
	(void)param;
}

int     main(int argc, char **argv)
{
	void		*scene;
	t_list	*json1;
	
	(void)argc;
    json1 = parse_json(argv[1]);
	scene = convert_objects(json1->content);
	t_list	*list = ft_libui_init();
	t_rect	r = ft_new_rect(WIN_X, WIN_Y, WIN_W, WIN_H);
	printf("\ny =========== %p\n", (void*)((t_scene*)scene)->objs);
	printf("\ny =========== %p\n", (void*)((t_scene*)scene)->objs);
	printf("\ny =========== %p\n", (void*)((t_scene*)scene)->objs);
	printf("\ny =========== %p\n", (void*)((t_scene*)scene)->objs);
	printf("\ny =========== %p\n", (void*)((t_scene*)scene)->objs);
	printf("\ny =========== %p\n", (void*)((t_scene*)scene)->objs);
	add_window((void**)&list, r, 0x00000000, "Ray Tracer v1.0");
	set_event_function(list->content, FT_EVENT_RENDER, ft_render, ft_get_window_pixels(list->content, NULL));
	set_event_function(list->content, FT_EVENT_KEYPRESS, ft_key_func, scene);
	ft_mainloop(list);
    return (0);
}

