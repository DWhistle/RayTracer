/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:21 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/30 15:32:10 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "ftui.h"
#include "effects.h"
#include <pthread.h>

#define NUMBER_OF_THREADS 16

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
	scene = 0;
	//if (scene->sepia)
	//	*color = sepia(*color);
	//if (scene->ce)
	//	*color = cartoon(*color);
	//if (scene->neg)
	//	*color = negative(*color);
	//if (scene->ster)
	//	*color = stereoscopy(*color, scene->ster);
	(*pixel)[pix] = (unsigned int)(color->arr[0]) << 16 |
				(unsigned int)(color->arr[1]) << 8 | (unsigned int)(color->arr[2]) | 0xff << 24;
}

void	effects2(t_scene *scene, int **pixel)
{
	if (scene->bm)
		*pixel = motion_blur(*pixel, scene->w, scene->h);
}


void	*pthread_antialiasing(void *p_param)
{
	t_pthread_param	*param;
	int				y;
	int				x;

	param = p_param;
	y = param->ymin;
	while (y < param->ymax)
	{
		x = -1;
		while (++x < param->x)
		{
			param->color = antialiasing(param->scene, (double)x / param->scene->w - 0.5,
				((double)y - param->scene->h * 0.5) / param->scene->h,
				param->scene->points_data + x + param->scene->w * y);
			if (param->accuracy.depth_pt != 1)
				param->color =
					vec_sum(param->scene->color[x + param->scene->w * y], param->color);
			param->color = check_color(param->color);
			param->scene->color[x + param->scene->w * y] =
				vec_dotdec(param->color, 1.0 / param->accuracy.depth_pt);
			effects1(param->scene, &(param->color), param->pixel, x + param->scene->w * y);
		}
		y++;
	}
	printf("%d - %d\n", param->ymin, param->ymax);
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

void	ft_wait_threads(pthread_t const *tread_ids, t_pthread_param **p_params)
{
	int		y;

	y = -1;
	while (++y < NUMBER_OF_THREADS)
	{
		pthread_join(tread_ids[y], NULL);
		free(p_params[y]);
	}
	free(p_params);
}

t_list	*pthread_init(t_scene *scene, int **pixel,
						t_accuracy accuracy)
{
	pthread_t 			tread_ids[NUMBER_OF_THREADS];
	t_pthread_param		**p_params;
	int					y;
	const int			step = scene->h / NUMBER_OF_THREADS;

	y = -1;
	p_params = ft_memalloc(sizeof(t_pthread_param *) * NUMBER_OF_THREADS);
	while (++y * step < scene->h - step)
	{
		p_params[y] = ft_memalloc(sizeof(t_pthread_param));
		p_params[y]->scene = scene;
		p_params[y]->x = scene->w;
		p_params[y]->ymin = y * step;
		p_params[y]->ymax = (((y + 1) * step) < scene->h - step)
				? (y + 1) * step
				: scene->h;
		p_params[y]->pixel = pixel;
		p_params[y]->accuracy = accuracy;
		pthread_create(&(tread_ids[y]), NULL,
				&pthread_antialiasing, (void *) p_params[y]);
	}
	ft_wait_threads(tread_ids, p_params);
	return (NULL);
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
	printf("%p",(void *)lst);
	//pthread_run(lst, scene);
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
