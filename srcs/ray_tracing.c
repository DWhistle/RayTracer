/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:21 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/09 16:09:00 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "ftui.h"
#include "effects.h"
#include <pthread.h>

t_vec	check_color(t_vec color)
{
	if (color.arr[0] > 255)
	{
		color.arr[1] += color.arr[0] - 255;
		color.arr[0] = 255;
	}
	if (color.arr[1] > 255)
	{
		color.arr[2] += color.arr[1] - 255;
		color.arr[1] = 255;
	}
	if (color.arr[2] > 255)
	{
		color.arr[0] += color.arr[2] - 255;
		color.arr[2] = 255;
	}
	if (color.arr[0] > 255)
		color.arr[0] = 255;
	return (color);
}

void	effects1(t_scene *scene, t_vec *color, int **pixel, int pix)
{
	if (scene->sepia)
		*color = sepia(*color);
	if (scene->ce)
		*color = cartoon(*color);
	if (scene->neg)
		*color = negative(*color);
	if (scene->ster)
		*color = stereoscopy(*color, scene->ster);
	(*pixel)[pix] = (int)(color->arr[0]) << 16 |
				(int)(color->arr[1]) << 8 | (int)(color->arr[2]) | 0xff << 24;
}

void	effects2(t_scene *scene, int **pixel)
{
	if (scene->bm)
		*pixel = motion_blur(*pixel, scene->w, scene->h);
}


void	*pthread_antialiasing(void *p_param)
{
	t_pthread_param	*param;

	param = p_param;
	param->color = antialiasing(param->scene, (double)param->x / param->scene->w - 0.5,
								((double)param->y - param->scene->h / 2) / param->scene->w,
								param->scene->points_data + param->x + param->scene->w * param->y);
	param->color = check_color(param->color);
	if (param->accuracy.depth_pt == 1)
		param->scene->color[param->x + param->scene->w * param->y] = param->color;
	else
		param->scene->color[param->x + param->scene->w * param->y] =
				vec_sum(param->scene->color[param->x + param->scene->w * param->y], param->color);
	param->color = vec_dotdec(param->scene->color[param->x + param->scene->w * param->y],
							  1.0 / param->accuracy.depth_pt);
	effects1(param->scene, &(param->color), param->pixel, param->x + param->scene->w * param->y);
	return (param);
}

t_list	*push_pthread(pthread_t *pid, t_list *lst)
{
	t_list	*new_thread;

	new_thread = ft_lstnew(pid, sizeof(pthread_t));
	ft_lstadd(&lst, new_thread);
	return (lst);
}

pthread_t	*pop_pthread(t_list *lst)
{
	pthread_t	*pid;

	pid = lst->content;
	ft_lstdelone(&lst, ft_bzero);
	lst = lst->next;
	return (pid);
}

t_list	*pthread_init(t_scene *scene, int **pixel,
						t_accuracy accuracy)
{
	pthread_t 			tread_id;
	t_pthread_param		*p_param;
	t_list				*lst;
	int					x;
	int					y;

	lst = NULL;
	y = scene->h;
	while (y--)
	{
		x = scene->w;
		while (x--)
		{
			p_param = ft_memalloc(sizeof(t_pthread_param));
			p_param->scene = scene;
			p_param->x = x;
			p_param->y = y;
			p_param->pixel = pixel;
			p_param->accuracy = accuracy;
			pthread_create(&tread_id, NULL, &pthread_antialiasing,
						   (void *) p_param);
			lst = push_pthread(&tread_id, lst);
		}
	}
	return (lst);
}

void	pthread_run(t_list *lst, t_scene *scene)
{
	int					x;
	int					y;
	pthread_t 			*pid;

	y = scene->h;
	while (y--)
	{
		x = scene->w;
		while (x--)
		{
			pid = pop_pthread(lst);
			pthread_join(*pid, NULL);
		}
	}
}

void	ray_tracing(t_scene *scene, int **pixel,
					t_accuracy accuracy)
{
	t_list	*lst;

	lst = pthread_init(scene, pixel, accuracy);
	pthread_run(lst, scene);
}

/*
void	ray_tracing(t_scene *scene, int **pixel,
					t_accuracy accuracy)
{
	int			x;
	int			y;
	t_vec		color;

	y = scene->h;
	while (y--)
	{
		x = scene->w;
		while (x--)
		{
			color = antialiasing(scene, (double)x / scene->w - 0.5,
			((double)y - scene->h / 2) / scene->w,\
			scene->points_data + x + scene->w * y);
			color = check_color(color);
			if (accuracy.depth_pt == 1)
				scene->color[x + scene->w * y] = color;
			else
				scene->color[x + scene->w * y] =\
				vec_sum(scene->color[x + scene->w * y], color);
			color = vec_dotdec(scene->color[x + scene->w * y],\
								1.0 / accuracy.depth_pt);
			effects1(scene, &color, pixel, x + scene->w * y);
		}
	}
	effects2(scene, pixel);
}
*/