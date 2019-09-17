/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:38:01 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/17 19:33:36 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __OPENCL_C_VERSION__
# include "ray_render.h"
#endif

float		maxcomp(t_vec p)
{
	return (fmax(p.vec.x, fmax(p.vec.y, p.vec.z)));
}

double		len_box(t_vec point, t_vec param)
{
	t_vec d;

	d = new_vec3(fabs(point.arr[0]), fabs(point.arr[1]), fabs(point.arr[2]));
	d = vec_sub(d, param);
	return (vec_len(vec_fmax(d, 0.0)) + fmin(fmax(d.arr[0],\
			fmax(d.arr[1], d.arr[2])), 0));
}

float		sd_cross(t_vec point, t_vec param)
{
	double da;
	double db;
	double dc;

	param.arr[0] = 0;
	da = maxcomp(vec_fabs(new_vec2(point.arr[0], point.arr[1])));
	db = maxcomp(vec_fabs(new_vec2(point.arr[1], point.arr[2])));
	dc = maxcomp(vec_fabs(new_vec2(point.arr[2], point.arr[0])));
	return (fmin(da, fmin(db, dc)) - 1.0);
}

double		len_box_fract(t_vec point, t_vec param)
{
	double	d;
	t_vec	a;
	double	s;
	double	c;
	int		m;

	s = 1.0;
	a = new_vec0();
	d = len_box(point, param);
	point = vec_sub(point, new_vec3(-1, -1, -1));
	m = -1;
	while (m++ < 4)
	{
		a = vec_dotdec(point, s);
		a.arr[0] = (fmod(a.arr[0], 2.0) - 1.0) * 3;
		a.arr[1] = (fmod(a.arr[1], 2.0) - 1.0) * 3;
		a.arr[2] = (fmod(a.arr[2], 2.0) - 1.0) * 3;
		s *= 3.0;
		c = (sd_cross(a, param)) / s;
		d = fmax(d, -c);
	}
	return (d);
}

double len_mandelbub(t_vec point, t_vec param)
{
	t_vec w = point;
    float m = vec_dotvec(w,w);

    t_vec trap = vec_fabs(w);
	trap.arr[3] = m;
	float dz = 1.0;

	for( int i=0; i < param.arr[0]; i++ )
    {
        float m2 = m*m;
        float m4 = m2*m2;
		dz = 8.0*sqrt(m4*m2*m)*dz + 1.0;

        float x = w.vec.x; float x2 = x*x; float x4 = x2*x2;
        float y = w.vec.y; float y2 = y*y; float y4 = y2*y2;
        float z = w.vec.z; float z2 = z*z; float z4 = z2*z2;

        float k3 = x2 + z2;
        float k2 = 1 / sqrt( k3*k3*k3*k3*k3*k3*k3 );
        float k1 = x4 + y4 + z4 - 6.0*y2*z2 - 6.0*x2*y2 + 2.0*z2*x2;
        float k4 = x2 - y2 + z2;

        w.vec.x = point.vec.x +  64.0*x*y*z*(x2-z2)*k4*(x4-6.0*x2*z2+z4)*k1*k2;
        w.vec.y = point.vec.y + -16.0*y2*k3*k4*k4 + k1*k1;
        w.vec.z = point.vec.z +  -8.0*y*k4*(x4*x4 -\
		28.0*x4*x2*z2 + 70.0*x4*z4 - 28.0*x2*z2*z4 + z4*z4)*k1*k2;

        m = vec_dotvec(w,w);
		if( m > 256.0 )
            break;
    }
    return 0.25*log(m)*sqrt(m)/dz;
}
