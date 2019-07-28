/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:31:11 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/28 16:20:07 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"
#include "parser.h"

int			check_names_obj(char *name)
{
	return (!ft_strncmp(name, "sphere", 6)
	|| !ft_strncmp(name, "tor", 3)
			|| !ft_strncmp(name, "plane", 5)
			|| !ft_strncmp(name, "cylinder", 8)
			|| !ft_strncmp(name, "box", 3)
			|| !ft_strncmp(name, "octahedron", 10)
			|| !ft_strncmp(name, "ellipsoid", 9)
			|| !ft_strncmp(name, "capsule", 7)
			|| !ft_strncmp(name, "triangular_prism", 16)
			|| !ft_strncmp(name, "hexagonal_prism", 15)
			|| !ft_strncmp(name, "cone", 4));
}

void		get_light(t_json *obj, char *name, t_light *light)
{
	t_json *json;

	json = (t_json*)query_attribute(obj, name).json_value;
	light->type = query_attribute(json, "type").int_value;
	light->intensity = query_attribute(json, "intensity").float_value;
	light->r = query_attribute(json, "radius").float_value;
	light->point = get_vec(query_attribute(json, "point").json_value);
	light->vec = get_vec(query_attribute(json, "vec").json_value);
}

t_scene		*get_scene(t_json *obj)
{
	t_scene *scene;

	scene = (t_scene*)ft_memalloc(sizeof(t_scene));
	scene->cam = new_vec3(0, 0, 0);
	scene->ignore = NULL;
	scene->bm = query_attribute(obj, "blur motion").int_value;
	scene->ce = query_attribute(obj, "cartoon effect").int_value;
	scene->neg = query_attribute(obj, "negative").int_value;
	scene->sepia = query_attribute(obj, "sepia").int_value;
	scene->ster = query_attribute(obj, "stereoscopy").int_value;
	return (scene);
}

void		*convert_objects(t_json *j)
{
	int		i;
	char	**obj;
	t_scene	*sc;

	sc = get_scene(j);
	i = 0;
	sc->number_objs = get_names_obj(j, &obj, check_names_obj);
	sc->objs = ft_memalloc(sizeof(t_obj) * sc->number_objs);
	while (i != sc->number_objs)
	{
		get_obj(j, obj[i], sc->objs + i);
		i++;
	}
	sc->number_lights = get_names_obj(j, &obj, check_names_light);
	sc->lights = ft_memalloc(sizeof(t_obj) * sc->number_lights);
	i = 0;
	while (i != sc->number_lights)
	{
		get_light(j, obj[i], sc->lights + i);
		i++;
	}
	return (sc);
}
