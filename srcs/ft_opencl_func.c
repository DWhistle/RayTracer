/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl_func.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 21:03:42 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_opencl_func.h"
#include "libft.h"
#include <stdio.h>

int			init_cl(t_opencl **cl)
{
	int		ret;

	if (!cl)
		return (0);
	*cl = ft_memalloc(sizeof(t_opencl));
	ret = clGetPlatformIDs(1, &((*cl)->platform_id),
			&((*cl)->ret_num_platforms));
	if (ret)
		return (0);
	ret = clGetDeviceIDs((*cl)->platform_id, CL_DEVICE_TYPE_GPU, 1,
			&((*cl)->device_id), &((*cl)->ret_num_devices));
	if (ret)
		return (0);
	(*cl)->context = clCreateContext(NULL, 1, &((*cl)->device_id),
			NULL, NULL, &ret);
	if (ret)
		return (0);
	(*cl)->command_queue = clCreateCommandQueue((*cl)->context,
			(*cl)->device_id, 0, &ret);
	return (ret ? 0 : 1);
}

void		print_log(t_opencl *cl)
{
	size_t		log_size;
	char		*log;

	clGetProgramBuildInfo(cl->program, cl->device_id,
			CL_PROGRAM_BUILD_LOG, 0, NULL, &log_size);
	log = (char *)malloc(log_size);
	clGetProgramBuildInfo(cl->program, cl->device_id,
			CL_PROGRAM_BUILD_LOG, log_size, log, NULL);
	ft_putendl(log);
	clGetProgramBuildInfo(cl->program, cl->device_id,
					CL_PROGRAM_BUILD_OPTIONS, 0, NULL, &log_size);
	ft_memdel((void*)&log);
	log = (char *)malloc(log_size);
	clGetProgramBuildInfo(cl->program, cl->device_id,
					CL_PROGRAM_BUILD_OPTIONS, log_size, log, NULL);
	ft_putendl(log);
}

int			compile_cl_by_name(t_opencl *cl, const char *name)
{
	cl_int	ret;
	char	*source_str;
	size_t	source_size;

	source_size = text_from_file(ft_get_cl_name(name, "cl/"), &source_str);
	if (source_size <= 0)
		return (0);
	cl->program = clCreateProgramWithSource(
			cl->context, 1, (const char **)&source_str,
			(const size_t *)&source_size, &ret);
	if (ret)
		return (0);
	ret = clBuildProgram(cl->program, 1, &(cl->device_id), NULL, NULL, NULL);
	if (ret)
	{
		print_log(cl);
		return (0);
	}
	cl->kernel = clCreateKernel(cl->program,
								"ray_tracing", &ret);
	return (ret ? 0 : 1);
}

int			run_queue(t_opencl *cl, size_t parallels)
{
	int		ret;

	ret = clEnqueueNDRangeKernel(
			cl->command_queue,
			cl->kernel, 1, NULL,
			&parallels, NULL, 0, NULL, NULL);
	return (!ret);
}
