#ifndef EFFECTS_H
# define EFFECTS_H

# include "vector.h"

t_vec4	cartoon(t_vec4 color);
t_vec4	negative(t_vec4 color);
t_vec4	sepia(t_vec4 color);
t_vec4	stereoscopy(t_vec4 color, int i);
int		*motion_blur(int *pixels, int w, int h);

#endif
