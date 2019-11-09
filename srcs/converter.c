/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:31:11 by bturcott          #+#    #+#             */
/*   Updated: 2019/11/09 15:49:00 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

void	get_rot(t_json *obj, t_scene *scene)
{
	int		res;
	t_vec	vec;
	int		signx;
	int		signy;

	vec = vec_norm(get_vec(query_attribute(obj, "direction", &res).json_value));
	signx = vec.arr[0] > 0 ? 1 : -1;
	signy = vec.arr[1] > 0 ? 1 : -1;
	scene->signz = vec.arr[2] > 0 ? 1 : -1;
	vec.arr[2] = fabs(vec.arr[2]);
	scene->rot_x = create_quat(new_vec3(1, 0, 0),\
					acos(vec_dotvec(new_vec3(0, 0, 1),\
					vec_norm(new_vec3(0, vec.arr[1], vec.arr[2])))) * signy);
	scene->rot = create_quat(new_vec3(0, 1, 0),\
					acos(vec_dotvec(new_vec3(0, 0, 1),\
					vec_norm(new_vec3(vec.arr[0], 0, vec.arr[2])))) * signx);
}

void	get_scene2(t_json *obj, t_scene *scene)
{
	int		res;

	scene->w = query_attribute(obj, "w", &res).int_value;
	if (res)
		scene->w = 0;
	scene->h = query_attribute(obj, "h", &res).int_value;
	if (res)
		scene->h = 0;
	scene->bm = query_attribute(obj, "blur motion", &res).int_value;
	if (res)
		scene->bm = 0;
	scene->ce = query_attribute(obj, "cartoon effect", &res).int_value;
	if (res)
		scene->ce = 0;
	scene->neg = query_attribute(obj, "negative", &res).int_value;
	if (res)
		scene->neg = 0;
	scene->sepia = query_attribute(obj, "sepia", &res).int_value;
	if (res)
		scene->sepia = 0;
	scene->ster = query_attribute(obj, "stereoscopy", &res).int_value;
	if (res)
		scene->ster = 0;
}

t_scene	*get_scene(t_json *obj)
{
	t_scene	*scene;
	int		res;

	scene = (t_scene*)ft_memalloc(sizeof(t_scene));
	scene->cam = get_vec(query_attribute(obj, "cam", &res).json_value);
	printf("%f\n", scene->cam.arr[0]);
	if (res)
		scene->cam = new_vec0();
	get_rot(obj, scene);
	scene->ignore = NULL;
	get_scene2(obj, scene);
	scene->color = ft_memalloc(sizeof(t_vec) * scene->w * scene->w);
	scene->points_data = ft_memalloc(sizeof(t_point_data) *\
									scene->w * scene->h);
	scene->accuracy = get_accuracy(obj);
	scene->fow = query_attribute(obj, "FOW", &res).float_value * (PI / 180.0);
	if (res)
		scene->fow = 1.5;
	return (scene);
}

int		check_names_light(char *name)
{
	return (!ft_strncmp(name, "light", 4));
}

void	*convert_objects(t_json *j)
{
	int		i;
	char	**obj;
	t_scene	*sc;

	sc = get_scene(j);
	sc->number_objs = gate_names_obj(j, &obj, check_names_obj);
	sc->objs = ft_memalloc(sizeof(t_obj) * sc->number_objs);
	i = 0;
	while (i != sc->number_objs)
	{
		get_obj(j, obj[i], sc->objs + i);
		i++;
	}
	sc->number_lights = gate_names_obj(j, &obj, check_names_light);
	sc->lights = ft_memalloc(sizeof(t_obj) * sc->number_lights);
	i = 0;
	while (i != sc->number_lights)
	{
		get_light(j, obj[i], sc->lights + i);
		i++;
	}
	return (sc);
}
