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
	DIRECT = 1,
	AMBIENT = 2,
	POINT = 3
};

typedef t_vec4 t_vec;

typedef struct s_obj2
{
	int		type;
	t_vec	point;
	t_vec	vec;
	double	r;
	double	angle;
	int		ind;
	double	reflection;
	t_vec	color;
}               t_obj2;

typedef struct s_obj
{
	int		type;
	void	*obj;
	int		ind;
	double	reflection;
	t_vec	color;
}               t_obj;

typedef struct	s_cylinder
{
	double	r;
	t_vec	vec;
	t_vec	point;
}				t_cylinder;

typedef struct	s_sphere
{
	double	r;
	t_vec	point;
}				t_sphere;

typedef struct	s_cone
{
	double 	angle;
	t_vec	vec;
	t_vec	point;
}				t_cone;

typedef struct	s_plane
{
	t_vec	point;
	t_vec	norm;
}				t_plane;

typedef struct	s_light
{
	double	intensity;
	int		ind;
}				t_light;

typedef struct	s_scene
{
	t_obj		*objs;
	int			number_objs;
	int			number_lights;
	t_vec		cam;
	t_light		*lights;
	t_obj		*ignore;
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
	//int		path;
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


#endif
