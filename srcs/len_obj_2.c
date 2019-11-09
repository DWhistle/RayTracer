/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_obj_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:45:18 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/11/09 15:49:20 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_render.h"

double	clamp1(double f, double s, double t)
{
	if (f < s)
		return (s);
	else if (f > t)
		return (t);
	else
		return (f);
}
