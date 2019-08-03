	#ifndef OBJECT_CL_H
# define OBJECT_CL_H


//#include "vector.h"
//#include "quat.h"
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

typedef double4 t_vec;
typedef double4 t_quat;

typedef struct s_obj
{
	int		type;
	t_quat	rot_quat;
	t_vec	point;
	double	rad;
	double	(*len)();
	int		ind;
	double	reflection;
	t_vec	color;
	double	refraction;
	t_vec	param;
	int		neg;
	double	fract;
}               t_obj;

typedef struct	s_light
{
	int		type;
	double	intensity;
	double	r;
	t_vec	point;
	t_vec	vec;
}				t_light;

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

typedef struct	s_scene
{
	t_obj		*objs;
	int			w;
	int			h;
	int			number_objs;
	int			number_lights;
	t_vec		cam;
	t_light		*lights;
	t_obj		*ignore;
	t_vec		*color;
	t_point_data		*points_data;
	int			ce;
	int			bm;
	int			neg;
	int			ster;
	int			sepia;
	t_accuracy	accuracy;
	int			sec;
}				t_scene;

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

#endif