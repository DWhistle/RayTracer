/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:49:11 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/09 15:46:39 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include "vector.h"
# include "quat.h"
# define MAX_Z 800
# define E 0.0001

enum
{
	NONE = 0,
	SPHERE = 1,
	PLANE = 2,
	CYLINDER = 3,
	CONE = 4,
	TOR = 5,
	MOBIUS = 6,
	BOX = 7,
	CROSS = 8,
	HEXAGONAL_PRISM = 9,
	TRIANGULAR_PRISM = 10,
	CAPSULE = 11,
	ELLIPSOID = 12,
	OCTAHEDRON = 13,
	MANDELBUB = 14,
	FRACTAL_BOX = 15,
	DIRECT = 1,
	AMBIENT = 2,
	POINT = 3
};

typedef t_vec4	t_vec;

typedef struct	s_texture
{
	int				h;
	int				w;
	double			len_u;
	double			len_v;
	unsigned char	*texture;
}				t_texture;

typedef struct	s_restriction
{
	t_vec	norm;
	t_vec	dislocation;
}				t_restriction;

typedef struct	s_obj
{
	int				type;
	t_quat			rot_quat;
	t_vec			point;
	double			rad;
	double			(*len)();
	int				ind;
	double			reflection;
	t_vec			color;
	double			refraction;
	double			tr_refraction;
	t_vec			param;
	int				neg;
	double			fract;
	t_texture		texture;
	int				numbers_plane;
	t_restriction	*restriction;
	double			frequency;
	int				specular;
	double			amplitude;
	t_texture		normal_map;
	double			transparency;
}				t_obj;

typedef struct	s_light
{
	int		type;
	double	intensity;
	double	r;
	t_vec	point	;
	t_vec	vec;
}				t_light;

typedef struct	s_point_data
{
	t_vec norm;
	t_obj *obj;
	t_vec point;
	t_vec color;
	t_vec ref_color;
	t_vec refr_color;
	t_vec tranc_color;
}				t_point_data;

typedef struct	s_accuracy
{
	int		rpp;
	int		depth_march;
	int		depth_pt;
	int		depth_ref;
	int		max_dist;
	double	delta;
}				t_accuracy;

typedef struct	s_scene
{
	t_obj			*objs;
	int				w;
	int				h;
	int				number_objs;
	int				number_lights;
	t_vec			cam;
	t_light			*lights;
	t_obj			*ignore;
	t_vec			*color;
	t_point_data	*points_data;
	int				ce;
	int				bm;
	int				neg;
	int				ster;
	int				sepia;
	t_accuracy		accuracy;
	int				sec;
	double			fow;
	t_quat			rot_x;
	t_quat			rot;
	int				signz;
	double			tr_intensity;
}				t_scene;

typedef struct	s_polygon
{
	t_vec		*points;
	int			number_point;
	t_vec		*norm;
}				t_polygon;

typedef struct	s_triangle
{
	t_vec		a;
	t_vec		b;
	t_vec		c;
}				t_triangle;

typedef struct	s_segment
{
	t_vec		a;
	t_vec		b;
}				t_segment;

typedef struct	s_mandelbub
{
	double	m;
	double	dz;
	double	m2;
	double	m4;
	double	x;
	double	y;
	double	z;
	double	k3;
	double	k2;
	double	k1;
	double	k4;
	double	x2;
	double	y2;
	double	z2;
	double	x4;
	double	y4;
	double	z4;
	t_vec	w;
	t_vec	trap;
}				t_mandelbub;

typedef	struct	s_pthread_param
{
	int			x;
	int			y;
	t_vec		color;
	int			**pixel;
	t_accuracy	accuracy;
	t_scene		*scene;
}				t_pthread_param;

#endif
