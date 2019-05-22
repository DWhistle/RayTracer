#ifndef OBJECT_H
# define OBJECT_H

#include "vector.h"

enum
{
	CIRCLE = 1,
	PLANE = 2,
	CYLINDER = 3,
	CONE = 4,
	DIRECT = 1,
	AMBIENT = 2,
	POINT = 3
};

typedef t_vec4 t_vec;

typedef struct s_obj
{
	int		type;
	t_vec	color;
	void	*obj;
	double	light;
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
	t_vec	point;
	t_vec	norm;
	double	intensity;
	int		type;
}				t_light;

typedef struct	s_scene
{
	t_obj		*objs;
	int			number_objs;
	int			number_lights;
	t_vec		cam;
	t_light		*lights;
}				t_scene;

#endif
