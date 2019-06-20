#ifndef RAY_RENDER_H
# define RAY_RENDER_H
# include "objects.h" 
# include "SDL2/SDL.h"
# include "libft.h"
# include <math.h>

t_point_data   	path_tracing(t_scene scene, t_vec vec, t_accuracy accuracy, t_vec point);
void            ray_tracing(t_scene scene, int **pixel, t_accuracy accuracy, SDL_Surface *screen);
t_vec           antialiasing(t_scene scene, double x, double y, t_accuracy accuracy);
double          len_circle(t_vec point, t_sphere *sphere);
double          len_cone(t_vec point, t_cone *cone);
double          len_cylinder(t_vec point, t_cylinder *cylinder);
double          len_plane(t_vec point, t_plane *plane);
t_point_data    path_tracing(t_scene scene, t_vec vec, t_accuracy accuracy, t_vec point);
t_vec           ray_render(t_scene scene, t_vec point, t_accuracy accuracy);
t_point_data    raymarching(t_scene objs, t_vec vec, t_accuracy accuracy, t_vec point);
t_vec           get_normal(t_vec point, t_obj obj);
double          light_render(t_scene objs, t_point_data point_data, t_vec n);
double          update_r(double r, t_obj new_obj, t_vec point, t_scene objs);
t_vec           lightt(t_scene objs, t_vec vec,
							t_accuracy accuracy, t_vec point);
#endif
