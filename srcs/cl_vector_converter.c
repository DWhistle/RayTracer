/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_vector_converter.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 19:39:44 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/09/23 19:42:28 by hgreenfe         ###   ########.fr       */
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
	cl_double4	*ret;
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
