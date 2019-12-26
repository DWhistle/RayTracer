/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:50:53 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/12/20 20:45:51 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "light.h"

double			color_calc(t_scene *objs, t_vec vec,
			t_point_data *point_data, t_light_option lo)
{
	double			i;
	double			n_dot_l;
	t_accuracy		accuracy;

	i = 0.0;
	accuracy = objs->accuracy;
	accuracy.max_dist = lo.len;
	if (!get_shadow(objs, &lo, accuracy, *point_data))
	{
		n_dot_l = vec_dotvec(point_data->norm, lo.li);
		if (n_dot_l > 0)
			i += objs->lights[lo.number_lights].intensity *\
			(n_dot_l) * lo.tr_intensity;
		if (point_data->obj->specular > 0)
		{
			n_dot_l = vec_dotvec(get_ref_vec(*point_data,\
					vec_dotdec(lo.li, -1)), vec_norm(vec_dotdec(vec, -1)));
			if (n_dot_l > 0)
				i += objs->lights[lo.number_lights].intensity *\
					pow(n_dot_l, point_data->obj->specular) *\
objs->lights[lo.number_lights].intensity * (n_dot_l) * lo.tr_intensity;
		}
	}
	return (i);
}

double			light_math2(t_scene *objs, t_vec *li,
					t_point_data *point_data, int number_lights)
{
	*li = vec_sub(rand_point(objs->lights[number_lights].\
	point, objs->lights[number_lights].r), point_data->point);
	return (vec_len(*li));
}

t_vec			light_math(t_scene *objs,\
				t_vec vec, t_point_data *point_data)
{
	double			i;
	t_light_option	lo;

	i = 0.0;
	lo.number_lights = objs->number_lights;
	lo.len = objs->accuracy.max_dist;
	while (lo.number_lights--)
	{
		if (objs->lights[lo.number_lights].type == AMBIENT)
			i += objs->lights[lo.number_lights].intensity;
		else
		{
			if (objs->lights[lo.number_lights].type == DIRECT)
				lo.li = objs->lights[lo.number_lights].vec;
			else
				lo.len = light_math2(objs, &lo.li, point_data,\
				lo.number_lights);
			lo.li = vec_norm(lo.li);
			i += color_calc(objs, vec, point_data, lo);
		}
	}
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
