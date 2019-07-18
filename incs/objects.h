	#ifndef OBJECT_H
# define OBJECT_H

#ifndef __OPENCL_C_VERSION__
#include "vector.h"
#endif
#define MAX_Z 800
#define E 0.0001

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
	DIRECT = 1,
	AMBIENT = 2,
	POINT = 3
};

typedef t_vec4 t_vec;

typedef struct s_obj
{
	int		type;
	double	angle;
	t_vec	rot_vec;
	t_vec	point;
	double	rad;
	void	(*len)();
	int		ind;
	double	reflection;
	t_vec	color;
	double	refraction;
	t_vec	param;
}               t_obj;

typedef struct	s_light
{
	int		type;
	double	intensity;
	double	r;
	t_vec	point;
	t_vec	vec;
}				t_light;

typedef struct	s_scene
{
	t_obj		*objs;
	int			number_objs;
	int			number_lights;
	t_vec		cam;
	t_light		*lights;
	t_obj		*ignore;
	t_vec		*color;
	int			ce;
	int			bm;
	int			neg;
	int			ster;
	int			sepia;
}				t_scene;

typedef struct	s_point_data
{
	t_vec norm;
	t_obj *obj;
	t_vec point;
	t_vec color;
}				t_point_data;

typedef struct	s_accuracy
{
	int		rpp;
	int		depth_march;
	int		depth_pt;
	int 	depth_ref;
	int 	max_dist;
	double	delta;
}				t_accuracy;

typedef struct	s_polygon
{
	t_vec	*points;
	int		number_point;
	t_vec	*norm;
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

typedef struct	s_tor
{
	t_plane		plane;
	double		R;
	double		r;
}				t_tor;

typedef struct	s_mobius
{
	t_plane		plane;
	double		R;
	t_vec 		vec;
	t_vec		norm;
}				t_mobius;

typedef struct	s_box
{
	t_vec		point;
	t_vec		options;
}				t_box;

typedef struct	s_cross
{
	t_vec		point;
	t_vec		options;
}				t_cross;


#endif
