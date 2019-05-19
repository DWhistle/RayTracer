#ifndef OBJECT_H
# define OBJECT_H

#include "vector.h"

enum
{
	CIRCLE = 1,
	DIRECT = 1
};

typedef t_vec4 t_vec;

typedef struct s_obj
{
	int		type;
	int		color;
	double	r;
	t_vec	norm;
	double	angle;
	t_vec	point;
}               t_obj;

typedef struct	s_light
{
	t_vec	point;
	t_vec	norm;
	int		type;
}				t_light;

typedef struct	s_scene
{
	t_obj		*objs;
	int			number_objs;
	t_vec		cam;
	t_light		*lights;
}				t_scene;

#endif
