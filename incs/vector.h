/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 18:25:23 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/19 23:26:32 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H
# include "ft_types.h"

union					u_vec4
{
	struct				s_vec4
	{
		ft_decimal		x;
		ft_decimal		y;
		ft_decimal		z;
		ft_decimal		w;
	}					vec;
	ft_decimal			arr[4];
};

typedef union u_vec4	t_vec4;

typedef union u_vec4*	t_pvec4;

t_vec4					new_vec(ft_decimal val);
t_vec4					new_vec4(ft_decimal valx, ft_decimal valy, ft_decimal valz,
									ft_decimal valw);
t_vec4					new_vec3(ft_decimal valx, ft_decimal valy, ft_decimal valz);
t_vec4					new_vec2(ft_decimal valx, ft_decimal valy);
t_vec4					new_vec0(void);
t_vec4					vec_dotvec(t_vec4 v1, t_vec4 v2);
t_vec4					vec_dotdec(t_vec4 v1, ft_decimal val);
t_vec4					vec_mul(t_vec4 v1, t_vec4 v2);
ft_decimal				vec_sqrdist(t_vec4 vec);
t_vec4					vec_norm(t_vec4 v);
t_vec4					vec_sum(t_vec4 v1, t_vec4 v2);
t_vec4					vec_add(t_vec4 v1, ft_decimal val);
t_vec4					vec_sub(t_vec4 v1, t_vec4 v2);
int						vec_equ(t_vec4 v1, t_vec4 v2, ft_decimal eps);
int						vec_ident(t_vec4 v1, t_vec4 v2);
ft_decimal				vec_len(t_vec4 vec);

#endif
