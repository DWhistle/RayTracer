/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 21:30:48 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/09/28 11:05:19 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H
# include "ray_render.h"

int				get_shadow(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_point_data point_data);
double			color_calc(t_scene *objs, t_vec vec,
						t_point_data *point_data, t_vec li);
t_vec			light_math(t_scene *o,
				t_vec vec, t_point_data *pd);
t_point_data	update_p_d(t_point_data p_d, t_vec point,
							t_vec color, t_vec norm);
t_vec			lightt(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_point_data *point_data);
t_vec			rand_point(t_vec point, double r);
t_vec			get_uv_spehere(t_vec point);
t_vec			get_pixel(t_vec uv, t_texture texture);
t_vec			get_uv_cylinder(t_texture texture, t_vec point, double param);
t_vec			get_uv_cone(t_texture texture, t_vec point);
t_vec			get_uv_plane(t_texture texture, t_vec point);
t_vec			get_color_obj(t_point_data shadow);
t_point_data	get_transparency(t_scene *objs, t_vec vec,
							t_point_data point_data);
t_point_data	get_refraction(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_point_data point_data);
t_point_data	get_point(t_scene *objs, t_vec vec,
							t_accuracy accuracy);
t_point_data	operate_reflection(t_scene *scene,
							t_vec vec, t_point_data point_data);
t_point_data	operate_color(t_point_data point_data, float n);
#endif
