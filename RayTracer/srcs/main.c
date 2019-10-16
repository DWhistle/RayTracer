/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:56:13 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/10/13 21:10:17 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../incs/libft.h"
#include "SDL2/SDL.h"
#include <OpenGL/gl.h>
#include "objects.h"
#include "ray_render.h"
#include "libft.h"
#include <stdio.h>
#include "parser.h"
#include "ftui.h"
#include <time.h>

#define WIN_X   500
#define WIN_Y   500
#define WIN_W   600
#define WIN_H   600

int		render(void *window, t_scene *scene)
{
	t_rect				screen;
	int					*pixels;
	time_t				rawtime;
	struct tm			*timeinfo;

	time(&rawtime);
	timeinfo = localtime(&rawtime);
	pixels = ft_get_window_pixels(window, &screen);
	srand(time(NULL));
	scene->accuracy.depth_pt++;
	ray_tracing(scene, (int**)&(pixels), scene->accuracy);
	return (0);
}

void	ft_tickfunc(void *wnd, int n, void *param)
{
	(void)n;
	param = ft_get_window_input_param(wnd);
	render(wnd, (t_scene*)param);
}

void	ft_key_func(void *wnd, int n, void *param)
{
	(void)param;
	if (n == FTUI_KEY_ESCAPE)
	{
		ft_set_window_quit(wnd, 1);
	}
}

void	free_json(t_list *obj)
{
	t_json *json;

	json = (t_json *)obj->content;
	free_json_obj(json);
	free(obj);
}

int		main(int argc, char **argv)
{
	void	*scene;
	t_list	*json1;
	t_list	*list;
	t_rect	r;

	(void)argc;
	atexit(SDL_Quit);
	json1 = parse_json(argv[1]);
	if (json1 == NULL)
        exit(0);
	scene = convert_objects(json1->content);
	free_json(json1);
	list = ft_libui_init();
	r = ft_new_rect(WIN_X, WIN_Y, ((t_scene*)scene)->w, ((t_scene*)scene)->h);
	add_window((void**)&list, r, 0x00000000, "Ray Tracer v1.0");
	set_event_function(list->content, FT_EVENT_KEYPRESS, ft_key_func, scene);
	set_event_function(list->content, FT_EVENT_TICKFUNC, ft_tickfunc, NULL);
	ft_mainloop(list);
	return (0);
}
