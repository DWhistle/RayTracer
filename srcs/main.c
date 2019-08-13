/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 17:56:13 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/08/06 00:13:31 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/libft.h"
#include "SDL2/SDL.h"
#include <OpenGL/gl.h>
#include "objects.h"
#include "ray_render.h"
#include "ft_opencl_func.h"
#include "cl_objects_converter.h"
#include "libft.h"
#include <stdio.h>
#include "parser.h"
#include "ftui.h"
#include <time.h>

#define WIN_X   500
#define WIN_Y   500
#define WIN_W   600
#define WIN_H   600

int		print_error(int errnum)
{
	if (errnum == 1)
		ft_putendl("Error! SDL Init error");
	else if (errnum == 2)
		ft_putendl("Error! Create window error");
	return (0);
}

void 	ft_printmem(void *pxls, int w, int h)
{
	SDL_Surface	*surface;


	surface = SDL_CreateRGBSurfaceFrom(pxls, w, h, 32, 8, 0xff, 0xff00, 0xff0000, 0xff000000);
	SDL_SaveBMP(surface, "screenshot.bmp");
}

void	render_cl(t_opencl	*ocl, t_scene scene, int **pixels)
{
	cl_mem mem_pixels;
	cl_mem mem_color;
	//add_parameter(ocl, 1, &scene, sizeof(t_scene));
	if (!compile_cl_by_name(ocl, "render"))
		return ;
	add_parameter_i(ocl, 1, &(scene.number_objs));
	add_parameter_i(ocl, 1, &(scene.number_lights));
	add_parameter_i(ocl, 1, &(scene.w));
	add_parameter_i(ocl, 1, &(scene.h));
	add_parameter_f(ocl, 4, (scene.cam.arr));
	add_parameter(ocl, scene.number_lights,
			get_cl_all_lights(scene.lights, scene.number_lights),
			sizeof(t_light));
	add_parameter(ocl, scene.number_objs,
			get_many_cl_obj(scene.objs, scene.number_objs), sizeof(t_obj));
	add_parameter(ocl, scene.number_objs,
			get_cl_points(scene.points_data, scene.number_objs),
			sizeof(t_point_data));
	mem_color = add_parameter(ocl, scene.w * scene.h,
			get_cl_many_vec(scene.color, scene.w * scene.h), sizeof(cl_double4));
	add_parameter(ocl, 1, &(scene.accuracy), sizeof(t_accuracy));
	mem_pixels = add_parameter_i(ocl, scene.w * scene.h, *pixels);
	run_queue(ocl, scene.w * scene.h);
	get_parameter_i(ocl, scene.w * scene.h, mem_pixels, *pixels);
	get_parameter_f(ocl, scene.w * scene.h * 4, mem_color, (void*)scene.color);
	if (scene.accuracy.depth_pt == 10)
		ft_printmem(*pixels, scene.w, scene.h);
}

int		render(void *window, t_scene *scene)
{
	t_rect				screen;
	int					*pixels;
	time_t				rawtime;
	struct tm			*timeinfo;
	t_opencl			*ocl;

	init_cl(&ocl);
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	pixels = ft_get_window_pixels(window, &screen);
	srand(time(NULL));
	scene->accuracy.depth_pt++;
	//ray_tracing(scene, (int**)&(pixels), scene->accuracy);
	//ocl = ft_get_window_window_param(window);
	render_cl(ocl, *scene, &pixels);
	printf("%d\n", scene->accuracy.depth_pt);
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

int		main(int argc, char **argv)
{
	void	*scene;
	t_list	*json1;
	t_list	*list;
	t_rect	r;
	//t_opencl	*ocl;

	(void)argc;
	json1 = parse_json(argv[1]);
	scene = convert_objects(json1->content);
	list = ft_libui_init();
	r = ft_new_rect(WIN_X, WIN_Y, ((t_scene*)scene)->w, ((t_scene*)scene)->h);
	add_window((void**)&list, r, 0x00000000, "Ray Tracer v1.0");
	set_event_function(list->content, FT_EVENT_KEYPRESS, ft_key_func, scene);
	set_event_function(list->content, FT_EVENT_TICKFUNC, ft_tickfunc, NULL);
	//ft_set_window_window_param(list->content, ocl);
	ft_mainloop(list);
	return (0);
}
