/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_blendings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/22 23:40:52 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftui.h"
#include "SDL2/SDL.h"

#define MAX_F 255.0
#define MAX_I 255u

unsigned int	ft_mul_color(unsigned int color, double alpha)
{
	double			component;

	component = (color & MAX_I);
	component = (component * (alpha));
	component = component > MAX_F ? MAX_F : component;
	color = (color & 0xffffff00u) | (int)(component);
	component = ((color >> 8u) & MAX_I);
	component = (component * (alpha));
	component = component > MAX_F ? MAX_F : component;
	color = (color & 0xffff00ffu) | ((int)component << 8);
	component = ((color >> 16u) & MAX_I);
	component = (component * (alpha));
	component = component > MAX_F ? MAX_F : component;
	color = (color & 0xff00ffffu) | ((int)component << 16);
	return (color);
}

unsigned int	ft_add_color(unsigned int one, unsigned int two)
{
	unsigned char	comp1;
	unsigned char	comp2;
	unsigned char	res;
	unsigned int	ret;

	comp1 = (one >> 16u) & MAX_I;
	comp2 = (two >> 16u) & MAX_I;
	res = comp1 + comp2;
	ret = (res > MAX_I ? MAX_I : res) << 16u;
	comp1 = (one >> 8u) & MAX_I;
	comp2 = (two >> 8u) & MAX_I;
	res = comp1 + comp2;
	ret |= (res > MAX_I ? MAX_I : res) << 8u;
	comp1 = (one) & MAX_I;
	comp2 = (two) & MAX_I;
	res = comp1 + comp2;
	ret |= (res > MAX_I ? MAX_I : res);
	return (ret);
}

unsigned int	ft_blend(unsigned int src, unsigned int dst)
{
	unsigned int	color;
	double			srcalpha;
	double			dstalpha;

	srcalpha = ((src >> 24u) & MAX_I) / MAX_F;
	color = ft_mul_color(src, srcalpha);
	color = ft_add_color(color, ft_mul_color(dst, (1.0 - srcalpha)));
	color &= 0x00ffffffu;
	dstalpha = srcalpha + (((dst >> 24u) & MAX_I) / MAX_F * (1.0 - srcalpha));
	color |= ((unsigned int)(dstalpha * MAX_F)) << 24u;
	return (color);
}

void			ft_add_textures(void *dst, void *src, unsigned long size)
{
	size_t			i;

	i = 0;
	while (i < size)
	{
		((unsigned int*)dst)[i] =
				ft_blend(((unsigned int*)src)[i], ((unsigned int*)dst)[i]);
		++i;
	}
}
