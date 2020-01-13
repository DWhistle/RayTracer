/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:18:55 by kmeera-r          #+#    #+#             */
/*   Updated: 2020/01/13 20:05:13 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

int		get_mandelbub(t_json *json, t_obj *object)
{
	int		res;

	object->type = MANDELBUB;
	object->len = len_mandelbub;
	object->param = new_vec0();
	object->param = get_vec(query_attribute(json, "param", &res).json_value);
	if (res)
		object->param = new_vec0();
	return (res);
}

void	get_obj2(t_json *json, t_obj *object)
{
	int			res;
	double		angle;
	t_vec		rotvec;

	object->transparency = query_attribute(json,\
							"transparency", &res).float_value;
	if (res)
		object->transparency = 0;
	object->frequency = query_attribute(json, "frequency", &res).float_value;
	if (res)
		object->frequency = 0;
	object->amplitude = query_attribute(json, "amplitude", &res).float_value;
	if (res)
		object->amplitude = 0;
	object->color = get_vec(query_attribute(json, "color", &res).json_value);
	if (res)
		object->color = new_vec0();
	angle = query_attribute(json, "angle", &res).float_value;
	if (res)
		angle = 0;
	rotvec = get_vec(query_attribute(json, "rot_vec", &res).json_value);
	if (res)
		rotvec = new_vec0();
	object->rot_quat = create_quat(vec_norm(rotvec), angle);
}

void	get_obj9(t_json *json, char *name, t_obj *object)
{
	if (ft_strncmp(name, "fract_box", 9) == 0)
		get_fract_box(json, object);
	else if (ft_strncmp(name, "mandelbub", 3) == 0)
		get_mandelbub(json, object);
}

void	get_obj3(t_json *json, char *name, t_obj *object)
{
	if (ft_strncmp(name, "sphere", 6) == 0)
		get_sphere(json, object);
	else if (ft_strncmp(name, "cone", 4) == 0)
		get_cone(json, object);
	else if (ft_strncmp(name, "cylinder", 8) == 0)
		get_cylinder(json, object);
	else if (ft_strncmp(name, "plane", 5) == 0)
		get_plane(json, object);
	else if (ft_strncmp(name, "tor", 3) == 0)
		get_tor(json, object);
	else if (ft_strncmp(name, "hexagonal_prism", 15) == 0)
		get_hexagonal_prism(json, object);
	else if (ft_strncmp(name, "triangular_prism", 16) == 0)
		get_triangular_prism(json, object);
	else if (ft_strncmp(name, "capsule", 7) == 0)
		get_capsule(json, object);
	else if (ft_strncmp(name, "ellipsoid", 9) == 0)
		get_ellipsoid(json, object);
	else if (ft_strncmp(name, "octahedron", 10) == 0)
		get_octahedron(json, object);
	else if (ft_strncmp(name, "box", 3) == 0)
		get_box(json, object);
	get_obj9(json, name, object);
}
