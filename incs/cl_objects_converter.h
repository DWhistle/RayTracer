/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_objects_converter.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 19:20:30 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/08/12 19:40:27 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CL_OBJECTS_CONVERTER_H
# define CL_OBJECTS_CONVERTER_H
# include "objects.h"
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

typedef struct			s_cl_obj
{
	int					type;
	cl_double4			rot_quat;
	cl_double4			point;
	cl_double4			color;
	cl_double4			param;
	double				rad;
	int					ind;
	double				reflection;
	double				refraction;
	int					neg;
	double				fract;
}						t_cl_obj;

typedef struct			s_cl_light
{
	int					type;
	double				intensity;
	double				r;
	cl_double4			point;
	cl_double4			vec;
}						t_cl_light;

typedef struct			s_cl_point_data
{
	cl_double4			norm;
	t_cl_obj			*obj;
	cl_double4			point;
	cl_double4			color;
}						t_cl_point_data;

typedef struct	        s_cl_accuracy
{
    int		            rpp;
    int		            depth_march;
    int		            depth_pt;
    int 	            depth_ref;
    int 	            max_dist;
    double	            delta;
}				        t_cl_accuracy;

typedef struct			s_cl_scene
{
	t_cl_obj			*objs;
	int					w;
	int					h;
	int					number_objs;
	int					number_lights;
	cl_double4			cam;
	t_cl_light			*lights;
	t_cl_obj			*ignore;
	cl_double4			*color;
	t_cl_point_data		*points_data;
	int					ce;
	int					bm;
	int					neg;
	int					ster;
	int					sepia;
	t_accuracy			*accuracy;
	int					sec;
}						t_cl_scene;

void					*get_zero_memory(size_t size);
t_cl_point_data			*get_cl_points(t_point_data *points, int count);
cl_double4				*get_cl_many_vec(t_vec *vec, int count);
t_cl_scene				*get_cl_scene(t_scene *scene);
t_cl_light				*get_cl_all_lights(t_light *light, int count);
t_cl_obj				*get_many_cl_obj(t_obj *objs, int count);
t_cl_obj				get_cl_obj(t_obj obj);
cl_double4				get_cl_vec(t_vec vec);
#endif
