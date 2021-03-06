/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl_params.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 21:57:30 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_opencl_func.h"

cl_mem		add_parameter(t_opencl *cl, int count,
				void *mem, unsigned long meme)
{
	cl_mem	memobj;
	cl_int	ret;

	memobj = clCreateBuffer(cl->context,
					CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
					count * meme, mem, &ret);
	if (ret)
		return (NULL);
	ret = clEnqueueWriteBuffer(cl->command_queue, memobj,
			CL_TRUE, 0, count * meme, mem, 0, NULL, NULL);
	if (ret)
		return (NULL);
	ret = clSetKernelArg(cl->kernel, cl->arg_count++,
					sizeof(cl_mem), (void *)&memobj);
	if (ret)
		return (NULL);
	return (memobj);
}

cl_mem		add_parameter_i(t_opencl *cl, int count, cl_int *mem)
{
	cl_mem	memobj;
	cl_int	ret;

	memobj = clCreateBuffer(cl->context,
					CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
					count * sizeof(cl_int), mem, &ret);
	if (ret)
		return (NULL);
	ret = clEnqueueWriteBuffer(cl->command_queue, memobj,
			CL_TRUE, 0, count * sizeof(cl_int), mem, 0, NULL, NULL);
	if (ret)
		return (NULL);
	ret = clSetKernelArg(cl->kernel, cl->arg_count++,
					sizeof(cl_mem), (void *)&memobj);
	if (ret)
		return (NULL);
	return (memobj);
}

cl_mem		add_parameter_f(t_opencl *cl, int count, cl_double *mem)
{
	cl_int	ret;
	cl_mem	memobj;

	memobj = clCreateBuffer(cl->context,
					CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
					count * sizeof(cl_double), mem, &ret);
	if (ret)
		return (NULL);
	ret = clEnqueueWriteBuffer(cl->command_queue, memobj, CL_TRUE, 0,
						count * sizeof(cl_double), mem, 0, NULL, NULL);
	if (ret)
		return (NULL);
	ret = clSetKernelArg(cl->kernel, cl->arg_count++, sizeof(cl_mem),
					(void *)&memobj);
	if (ret)
		return (NULL);
	return (memobj);
}

void		clear_parameters(t_opencl *cl)
{
	cl->arg_count = 0;
}
