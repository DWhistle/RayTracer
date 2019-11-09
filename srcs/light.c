/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:50:53 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/08 16:03:03 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

double			color_calc(t_scene *objs, t_vec vec,\
						t_point_data *point_data, t_vec li)
{
	double	i;
	double	n_dot_l;
	t_vec	hw_vec;

	i = 0.0;
	if (!get_shadow(objs, li, objs->accuracy, *point_data))
	{
		n_dot_l = vec_dotvec(point_data->norm, li);
		if (n_dot_l > 0)
			i += objs->lights[objs->number_lights].intensity *\
			(n_dot_l) * objs->tr_intensity;
		if (point_data->obj->specular > 0)
		{
			hw_vec = vec_norm(vec_sum(vec_dotdec(li, 1),\
					vec_norm(vec_dotdec(vec, -1))));
			n_dot_l = vec_dotvec(hw_vec, point_data->norm);
			n_dot_l = vec_dotvec(get_ref_vec(*point_data,\
					vec_dotdec(li, -1)), vec_norm(vec_dotdec(vec, -1)));
			if (n_dot_l > 0)
				i += objs->lights[objs->number_lights].intensity *\
					pow(n_dot_l, point_data->obj->specular) *\
objs->lights[objs->number_lights].intensity * (n_dot_l) * objs->tr_intensity;
		}
	}
	return (i);
}

void			light_math2(t_scene *objs, t_vec *li, t_point_data *point_data)
{
	*li = vec_sub(rand_point(objs->lights[objs->number_lights].\
	point, objs->lights[objs->number_lights].r), point_data->point);
	objs->accuracy.max_dist = vec_len(*li);
}

t_vec			light_math(t_scene *objs,\
				t_vec vec, t_point_data *point_data)
{
	double	i;
	t_vec	li;
	int		n;
	int		len;

	i = 0.0;
	n = objs->number_lights;
	len = objs->accuracy.max_dist;
	while (objs->number_lights--)
		if (objs->lights[objs->number_lights].type == AMBIENT)
			i += objs->lights[objs->number_lights].intensity;
		else
		{
			if (objs->lights[objs->number_lights].type == DIRECT)
				li = objs->lights[objs->number_lights].vec;
			else
				light_math2(objs, &li, point_data);
			i += color_calc(objs, vec, point_data, vec_norm(li));
		}
	objs->accuracy.max_dist = len;
	objs->number_lights = n;
	return (vec_dotdec(point_data->color, i));
}

t_point_data	update_p_d(t_point_data p_d, t_vec point,\
							t_vec color, t_vec norm)
{
	p_d.point = point;
	p_d.color = color;
	p_d.norm = norm;
	return (p_d);
}

t_vec			lightt(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_point_data *point_data)
{
	*point_data = get_point(objs, vec, accuracy);
	if (!point_data->obj)
		return (new_vec0());
	return (point_data->color);
}
