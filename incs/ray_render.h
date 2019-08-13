#ifndef RAY_RENDER_H
# define RAY_RENDER_H
# include "objects.h" 
# include "SDL2/SDL.h"
# include "libft.h"
# include <math.h>
# include "quat.h"
# include "ftui.h"

t_point_data   	path_tracing(t_scene scene, t_vec vec, t_accuracy accuracy, t_vec point);
void            ray_tracing(t_scene *scene, int **pixel, t_accuracy accuracy);
t_vec			antialiasing(t_scene *scene, double x, double y, t_point_data *point_data);
double			len_sphere(t_vec point, t_vec param);
double          len_cone(t_vec point, t_vec param);
double          len_cylinder(t_vec point, t_vec param);
double          len_plane(t_vec point, t_vec param);
double			len_tor(t_vec point, t_vec param);
double			len_box(t_vec point, t_vec param);
double			len_octahedron(t_vec point, t_vec param);
double			len_ellipsoid(t_vec point, t_vec param);
double			len_capsule(t_vec point, t_vec param);
double			len_triangular_prism(t_vec point, t_vec param);
double			len_hexagonal_prism(t_vec point, t_vec param);
t_point_data    path_tracing(t_scene scene, t_vec vec, t_accuracy accuracy, t_vec point);
t_point_data	ray_render(t_scene *scene, t_vec vec, t_vec point, t_point_data (*raymarch)());
t_point_data    raymarching(t_scene *objs, t_vec vec, t_accuracy accuracy, t_vec point);
t_vec			get_normal(t_vec point, t_obj obj);
double          light_render(t_scene objs, t_point_data point_data, t_vec n);
double			update_r(t_obj new_obj, t_vec point);
t_vec			lightt(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_point_data *point_data);
t_vec			transparency(t_vec vec, t_point_data point);
t_point_data	crate_point_data(t_vec norm,
				t_obj *obj, t_vec point, t_vec color);
t_vec			rot(t_quat quat, t_vec v);
t_vec			get_ref_vec(t_point_data point_data, t_vec vec);
double			clamp1(double f, double s, double t);
t_point_data	shadowmarching(t_scene *objs, t_vec vec,
							t_accuracy accuracy, t_vec point);
t_point_data	raymarch_in_obj(t_obj *obj, t_vec vec,
							t_accuracy accuracy, t_vec point);
t_vec           get_pixel(t_vec uv, t_texture texture);
t_vec           get_uv_spehere(t_vec point);
t_vec           get_uv_cylinder(t_texture texture, t_vec point, double param);
t_vec           get_uv_cone(t_texture texture, t_vec point);
t_vec           get_uv_plane(t_texture texture, t_vec point);
t_vec           get_color_obj(t_point_data shadow);
double			len_mandelbub(t_vec point, t_vec param);
double			map(t_vec point, t_vec param);
#endif	
