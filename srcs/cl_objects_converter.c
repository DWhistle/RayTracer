/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_objects_converter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:27:27 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/08/12 19:47:36 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl_objects_converter.h"
#include "objects.h"
#include "libft.h"

cl_double4		get_cl_vec(t_vec vec)
{
	cl_double4 ret;

	ret.x = vec.vec.x;
	ret.y = vec.vec.y;
	ret.z = vec.vec.z;
	ret.w = vec.vec.w;
	return (ret);
}

cl_double4		*get_cl_many_vec(t_vec *vec, int count)
{
	cl_double4 *ret;
	int			i;

	if (!vec || !count)
		return (NULL);
	ret = ft_memalloc(sizeof(cl_double4) * count);
	if (!ret)
		return (NULL);
	i = 0;
	while (i < count)
	{
		ret[i].x = vec[i].vec.x;
		ret[i].y = vec[i].vec.y;
		ret[i].z = vec[i].vec.z;
		ret[i].w = vec[i].vec.w;
		++i;
	}
	return (ret);
}

t_cl_obj		get_cl_obj(t_obj obj)
{
	t_cl_obj	ret;

	ret.type = obj.type;
	ret.rot_quat = get_cl_vec(vec_from_quat(obj.rot_quat));
	ret.point = get_cl_vec(obj.point);
	ret.rad = obj.rad;
	ret.ind = obj.ind;
	ret.reflection = obj.reflection;
	ret.color = get_cl_vec(obj.color);
	ret.refraction = obj.refraction;
	ret.param = get_cl_vec(obj.param);
	ret.neg = obj.neg;
	ret.fract = obj.fract;
	return (ret);
}

t_cl_obj		*get_many_cl_obj(t_obj *objs, int count)
{
	int			i;
	t_cl_obj	*cl_obj;

	i = 0;
	if (!objs || !count)
		return ((t_cl_obj*)get_zero_memory(count * sizeof(t_cl_obj)));
	cl_obj = (t_cl_obj*)ft_memalloc(sizeof(t_cl_obj) * count);
	if (!cl_obj)
		return (NULL);
	while (i < count)
	{
		cl_obj[i] = get_cl_obj(objs[i]);
		++i;
	}
	return (cl_obj);
}

t_cl_light		*get_cl_all_lights(t_light *light, int count)
{
	t_cl_light	*cl_light;
	int			i;

	if (!light || !count)
	if (!light || !count)
		return ((t_cl_light*)get_zero_memory(count * sizeof(t_cl_light)));
	cl_light = (t_cl_light*)ft_memalloc(sizeof(t_cl_light) * count);
	if (!cl_light)
		return (NULL);
	i = 0;
	while (i < count)
	{
		cl_light[i].type = light[i].type;
		cl_light[i].intensity = light[i].intensity;
		cl_light[i].r = light[i].r;
		cl_light[i].point = get_cl_vec(light[i].point);
		cl_light[i].vec = get_cl_vec(light[i].vec);
		++i;
	}
	return (cl_light);
}

t_cl_point_data	*get_cl_points(t_point_data *points, int count)
{
	t_cl_point_data	*cl_point_data;
	int				i;

	if (!points)
		return (get_zero_memory(count * sizeof(t_cl_point_data)));
	cl_point_data = (t_cl_point_data*)ft_memalloc(sizeof(t_cl_point_data) * count);
	if (!cl_point_data)
		return (NULL);
	i = 0;
	while (i < count)
	{
		cl_point_data[i].color = get_cl_vec(points[i].color);
		cl_point_data[i].norm = get_cl_vec(points[i].norm);
		cl_point_data[i].point = get_cl_vec(points[i].point);
		cl_point_data[i].obj = get_many_cl_obj(points[i].obj, 1);
		++i;
	}
	return (cl_point_data);
}

void			*get_zero_memory(size_t size)
{
    if (size > 0)
        return (ft_memalloc(size));
    else
        return (NULL);
}
