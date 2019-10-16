/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_rander_cl.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 20:45:25 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/09/25 20:45:25 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_RANDER_CL_H
# define RAY_RANDER_CL_H
# include "../cl/objects_cl.h"
/*
**#  include "quat.h"
**
**t_point_data   	path_tracing(__global t_scene *scene, t_vec vec,
** t_accuracy accuracy, t_vec point);
**t_vec			antialiasing(t_scene *scene, double x, double y,
** t_accuracy accuracy, t_point_data *point_data);
**double			len_sphere(t_vec point, t_vec param);
**double          len_cone(t_vec point, t_vec param);
**double          len_cylinder(t_vec point, t_vec param);
**double          len_plane(t_vec point, t_vec param);
**double			len_tor(t_vec point, t_vec param);
**double			len_box(t_vec point, t_vec param);
**double			len_octahedron(t_vec point, t_vec param);
**double			len_ellipsoid(t_vec point, t_vec param);
**double			len_capsule(t_vec point, t_vec param);
**double			len_triangular_prism(t_vec point, t_vec param);
**double			len_hexagonal_prism(t_vec point, t_vec param);
**t_point_data    path_tracing(__global t_scene *scene, t_vec vec,
** t_accuracy accuracy, t_vec point);
**t_point_data    ray_render(__global t_scene *scene, t_vec point,
** t_accuracy accuracy);
**t_point_data    raymarching(t_scene objs, t_vec vec,
** t_accuracy accuracy, t_vec point);
**t_vec			get_normal(t_vec point, t_obj obj);
**double          light_render(__global t_scene *objs,
** t_point_data point_data, t_vec n);
**double			update_r(t_obj new_obj, t_vec point);
**t_vec			lightt(__global t_scene *objs, t_vec vec,
**							t_accuracy accuracy, t_point_data *point_data);
**t_vec			transparency(t_vec vec, t_point_data point);
**t_point_data	crate_point_data(t_vec norm,
**				t_obj *obj, t_vec point, t_vec color);
**t_vec			rot(t_quat quat, t_vec v);
**t_vec			get_ref_vec(t_point_data point_data, t_vec vec);
**int     get_shadow(__global t_scene *objs, t_vec vec,
**							t_accuracy accuracy, t_point_data point_data);
**t_point_data get_point(__global t_scene *objs, t_vec vec,
**							t_accuracy accuracy);
**t_vec			rand_point(t_vec point, double r);
**t_vec	f(t_point_data *points, int depth_ref, __global t_scene *scene);
**t_vec	get_ref_color(t_point_data *points);
**double			get_dist(int neg, t_obj **obj, t_vec point, t_scene scene);
*/
#endif
