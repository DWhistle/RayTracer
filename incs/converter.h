/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:18:57 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 12:31:06 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONVERTER_H
# define CONVERTER_H

# include "ray_render.h"
# include "parser.h"
# include "SDL2/SDL.h"
# define PI 3.14159265359

typedef struct	s_restr
{
	int				res;
	t_json			*json;
	char			**names;
	t_restriction	*r;
	int				n;
}				t_restr;

int				gate_names_obj(t_json *j, char ***names, int (*check_names)());
t_values		query_attribute(t_json *obj, char *name, int *res);
t_vec			get_vec(t_json *json);
int				get_sphere(t_json *json, t_obj *object);
int				get_cone(t_json *json, t_obj *object);
int				get_cylinder(t_json *json, t_obj *object);
int				get_plane(t_json *json, t_obj *object);
int				get_tor(t_json *json, t_obj *object);
int				get_hexagonal_prism(t_json *json, t_obj *object);
int				get_triangular_prism(t_json *json, t_obj *object);
int				get_capsule(t_json *json, t_obj *object);
int				get_ellipsoid(t_json *json, t_obj *object);
int				get_octahedron(t_json *json, t_obj *object);
int				get_box(t_json *json, t_obj *object);
int				get_mandelbub(t_json *json, t_obj *object);
t_texture		get_texture(t_json *j, char *name);
int				check_plane(char *name);
t_restriction	*get_restriction(t_json *j, int *ns_p);
void			get_obj2(t_json *json, t_obj *object);
void			get_obj3(t_json *json, char *name, t_obj *object);
void			get_obj4(t_json *json, t_obj *object);
void			get_obj(t_json *obj, char *name, t_obj *object);
int				check_names_obj(char *name);
void			get_light(t_json *obj, char *name, t_light *light);
t_accuracy		get_accuracy(t_json *obj);
void			get_rot(t_json *obj, t_scene *scene);
void			get_scene2(t_json *obj, t_scene *scene);
t_scene			*get_scene(t_json *obj);
int				check_names_light(char *name);
void			*convert_objects(t_json *j);

#endif
