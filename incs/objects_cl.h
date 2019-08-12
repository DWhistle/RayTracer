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
	t_vec	color;
	t_vec	param;
	double	rad;
	int		ind;
	double	reflection;
	double	refraction;
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
	__global t_obj *obj;
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
    __global t_obj		    *objs;
	int			            w;
	int			            h;
	int			            number_objs;
	int			            number_lights;
	t_vec		            cam;
    __global t_light	    *lights;
    __global t_obj		    *ignore;
    __global t_vec		    *color;
    __global t_point_data	*points_data;
	int			            ce;
	int			            bm;
	int			            neg;
	int			            ster;
	int			            sepia;
    __global t_accuracy	    *accuracy;
	int			            sec;
}				            t_scene;

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

t_obj	        *get_objects(__global t_obj *objects, int count);
t_point_data	raymarching(t_scene scene,
                            double4 vec,
                            t_vec point);
t_vec			get_normal(t_vec point, t_obj obj);
double			get_dist(int neg,
                           __global t_obj **obj,
                           t_vec point,
                           t_scene scene);
double			update_r(t_obj new_obj, t_vec point);
double			ft_len(t_obj obj, t_vec point);
t_vec			rot(t_quat quat, t_vec v);
t_point_data	crate_point_data(t_vec norm,
                                 __global t_obj *obj, t_vec point, t_vec color);
t_vec			rand_point(t_vec point, double r);

#endif