/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:25:23 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/11/09 11:51:36 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# ifndef __OPENCL_C_VERSION__
#  include <math.h>
# endif

typedef	double	t_decimal;

union					u_vec4
{
	struct				s_vec4
	{
		t_decimal		x;
		t_decimal		y;
		t_decimal		z;
		t_decimal		w;
	}					vec;
	t_decimal			arr[4];
};

typedef union u_vec4	t_vec4;

typedef union u_vec4*	t_pvec4;

t_vec4					new_vec(t_decimal val);
t_vec4					new_vec4(t_decimal valx, t_decimal valy,
								t_decimal valz,
									t_decimal valw);
t_vec4					new_vec3(t_decimal valx, t_decimal valy,
								t_decimal valz);
t_vec4					new_vec2(t_decimal valx, t_decimal valy);
t_vec4					new_vec0(void);
double					vec_dotvec(t_vec4 v1, t_vec4 v2);
t_vec4					vec_dotdec(t_vec4 v1, t_decimal val);
t_vec4					vec_mul(t_vec4 v1, t_vec4 v2);
t_decimal				vec_sqrdist(t_vec4 vec);
t_vec4					vec_norm(t_vec4 v);
t_vec4					vec_sum(t_vec4 v1, t_vec4 v2);
t_vec4					vec_add(t_vec4 v1, t_decimal val);
t_vec4					vec_sub(t_vec4 v1, t_vec4 v2);
int						vec_equ(t_vec4 v1, t_vec4 v2, t_decimal eps);
int						vec_ident(t_vec4 v1, t_vec4 v2);
t_decimal				vec_len(t_vec4 vec);
t_vec4					vec_fabs(t_vec4 vec);
t_vec4					vec_fabs(t_vec4 vec);
t_vec4					vec_fmin(t_vec4 vec, double n);
t_vec4					vec_fmax(t_vec4 vec, double n);

#endif
