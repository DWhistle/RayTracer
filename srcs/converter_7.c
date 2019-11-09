/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:18:55 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

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
}
