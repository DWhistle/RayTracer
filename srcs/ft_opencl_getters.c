/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl_getters.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/10 19:30:35 by bturcott          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_opencl_func.h"

int			get_parameter_i(t_opencl *cl, int count, cl_mem memobj, cl_int *mem)
{
	int		ret;

	ret = clEnqueueReadBuffer(cl->command_queue,
					memobj, CL_TRUE, 0, count * sizeof(cl_int),
					mem, 0, NULL, NULL);
	return (!ret);
}

int			get_parameter_f(t_opencl *cl, int count, cl_mem memobj,
		cl_double *mem)
{
	int		ret;

	ret = clEnqueueReadBuffer(cl->command_queue,
					memobj, CL_TRUE, 0,
					count * sizeof(cl_double),
					mem, 0, NULL, NULL);
	return (!ret);
}

int			get_parameter(t_opencl *cl, size_t memsize, cl_mem memobj,
						cl_double *mem)
{
	int		ret;

	ret = clEnqueueReadBuffer(cl->command_queue,
						memobj, CL_TRUE, 0,
						memsize,
						mem, 0, NULL, NULL);
	return (!ret);
}
