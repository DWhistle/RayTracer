/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raymarching.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 13:07:11 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYMARCHING_H
# define RAYMARCHING_H

# include <math.h>
# include "ray_render.h"
# include "libft.h"
# include <stdio.h>

double			mix(double x, double y, double a);
double			smooth_union(double d1, double d2, double k);
double			update_restriction(double r, t_obj obj, t_vec point);
double			displace(t_vec point, double r, t_obj obj);
double			onion(double len, double h);
double			update_r(t_obj new_obj, t_vec point);
t_vec			normal_map(t_vec point, t_obj obj);
t_vec			get_normal(t_vec point, t_obj obj);
t_point_data	crate_point_data(t_vec norm,
				t_obj *obj, t_vec point, t_vec color);
double			get_dist(int neg, t_obj **obj, t_vec point, t_scene *scene);
t_point_data	raymarch_in_obj(t_obj *obj, t_vec vec,
							t_accuracy accuracy, t_vec point);
t_point_data	raymarching(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_vec point);
t_point_data	shadowmarching(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_vec point);

#endif
