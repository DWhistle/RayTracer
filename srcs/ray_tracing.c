/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:10:21 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/12/20 19:38:54 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "ftui.h"
#include "effects.h"
#include <pthread.h>

#define NUMBER_OF_THREADS 16

int		ft_wait_threads(pthread_t const *tread_ids, t_pthread_param **p_params)
{
	int		y;

	y = -1;
	while (++y < NUMBER_OF_THREADS)
	{
		pthread_join(tread_ids[y], NULL);
		free(p_params[y]);
	}
	free(p_params);
	return (0);
}

int		pthread_init(t_scene *scene, int **pixel,
		t_accuracy accuracy)
{
	pthread_t			tread_ids[NUMBER_OF_THREADS];
	t_pthread_param		**p_params;
	int					y;
	const int			step = scene->h / NUMBER_OF_THREADS;

	y = -1;
	if (step < 2)
		return (1);
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
		p_params[y]->color = new_vec(0);
		p_params[y]->pixel = pixel;
		p_params[y]->accuracy = accuracy;
		pthread_create(tread_ids + y, NULL,
				&pthread_antialiasing, (void *)p_params[y]);
	}
	return (ft_wait_threads(tread_ids, p_params));
}

void	ray_tracing(t_scene *scene, int **pixel,
		t_accuracy accuracy)
{
	if (pthread_init(scene, pixel, accuracy))
	{
		ft_putendl("irrelevant window height");
		exit(0);
	}
}
