/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 12:31:49 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/02 12:31:58 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EFFECTS_H
# define EFFECTS_H

# include "vector.h"

typedef struct	s_motion_blur
{
	int x;
	int y;
	int r;
	int g;
	int b;
	int a;
}				t_motion_blur;

t_vec4			cartoon(t_vec4 color);
t_vec4			negative(t_vec4 color);
t_vec4			sepia(t_vec4 color);
t_vec4			stereoscopy(t_vec4 color, int i);
int				*motion_blur(int *pixels, int w, int h);

#endif
