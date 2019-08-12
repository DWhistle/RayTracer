/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl_func.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/14 21:19:48 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/08/12 19:53:33 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OPENCL_FUNC_H
# define FT_OPENCL_FUNC_H
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# define BUFFER_SIZE	255
# define MAX_SOURCE_SIZE 5000

typedef	struct			s_opencl {
	cl_uint				ret_num_platforms;
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_uint				ret_num_devices;
	cl_context			context;
	cl_command_queue	command_queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_uint				arg_count;
}						t_opencl;

void		            print_log(t_opencl *cl);
int						init_cl(t_opencl **cl);
int						compile_cl_by_name(t_opencl *cl,
											const char *name);
cl_mem					add_parameter_i(t_opencl *cl, int count, cl_int *mem);
cl_mem					add_parameter_f(t_opencl *cl, int count,
											cl_double *mem);
int						run_queue(t_opencl *cl, size_t parallels);
int						get_parameter_i(t_opencl *cl, int num, cl_mem memobj,
											cl_int *mem);
int						get_parameter(t_opencl *cl, int count, cl_mem memobj,
										cl_double *mem, size_t memsize);
void					clear_parameters(t_opencl *cl);
int						get_parameter_f(t_opencl *cl, int count, cl_mem memobj,
											cl_double *mem);
size_t					text_from_file(const char *filename,
											char **file_content);
char					*ft_get_cl_name(const char *name, char *dirname);
cl_mem					add_parameter(t_opencl *cl, int count, void *mem, unsigned long meme);

#endif
