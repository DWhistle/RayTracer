

# ifndef __OPENCL_C_VERSION__
#  include "ray_render.h"
# endif

double clamp1(double f, double s, double t)
{
	if (f < s)
		return (s);
	else if (f > t)
		return (t);
	else
		return (f);
}

double	len_sphere(t_vec point, t_vec param)
{
	return (vec_len(point) - fabs(param.arr[0]));
}

double	len_cone(t_vec point, t_vec param)
{
	double q;

	q = vec_len(new_vec2(point.arr[0], point.arr[1]));
	return (fmin(vec_dotvec(param, new_vec2(q, point.arr[2])),
				vec_dotvec(new_vec2(param.arr[0], -param.arr[1]), new_vec2(q, point.arr[2]))));
}	

double	len_cylinder(t_vec point, t_vec param)
{
	return (vec_len(vec_sub(new_vec2(point.arr[0], point.arr[2]),\
			new_vec2(param.arr[0], param.arr[1]))) - param.arr[2]);
}

double	len_plane(t_vec point, t_vec param)
{
	t_vec norm;
	norm = new_vec3(param.arr[0], param.arr[1], param.arr[2]);
	return (vec_dotvec(point, norm) + param.arr[3]);
}

double	len_tor(t_vec point, t_vec param)
{
	t_vec q;
	q = new_vec2(vec_len(new_vec2(point.arr[0], point.arr[2])) - param.arr[0], point.arr[1]);
	return (vec_len(q) - param.arr[1]);
}

double len_hexagonal_prism(t_vec point, t_vec param)
{
	const t_vec	k = new_vec3(-0.8660254, 0.5, 0.57735);
	t_vec		vec;
	t_vec		d;

	point = vec_fabs(point);
	vec = vec_dotdec(new_vec2(k.arr[0], k.arr[1]),\
		2.0 * fmin(vec_dotvec(new_vec2(k.arr[0], k.arr[1]),\
		new_vec2(point.arr[0], point.arr[1])), 0));
	point = vec_sub(point, vec);
	d = new_vec2(vec_len(vec_sub(new_vec2(point.arr[0], point.arr[1]),\
		new_vec2(clamp1(point.arr[0], -k.arr[2] * param.arr[0],\
		k.arr[2] * param.arr[0]), param.arr[0])))\
		* point.arr[1] - param.arr[0] > 0 ? 1 : -1,\
		point.arr[2] - param.arr[1]);
	return (fmin(fmax(d.arr[0], d.arr[1]), 0) +  vec_len(vec_fmax(d, 0)));
}

double len_triangular_prism(t_vec point, t_vec param)
{
	t_vec	q;
	q = vec_fabs(point);
	return (fmax(q.arr[2] - param.arr[1],\
			fmax(q.arr[0] * 0.866025 + point.arr[1] * 0.5,\
			-point.arr[1]) - param.arr[0] * 0.5));
}

double	len_capsule(t_vec point, t_vec param)
{
	point.arr[1] -= clamp1(point.arr[1], 0.0, param.arr[0]);
	return (vec_len(point) - param.arr[1]);
}

double	len_ellipsoid(t_vec point, t_vec param)
{
	double k0;
	double k1;

	k0 = vec_len(new_vec3(point.arr[0] / param.arr[0], point.arr[1] / param.arr[1], point.arr[2] / param.arr[2]));
	k1 = vec_len(new_vec3(point.arr[0] / param.arr[0] / param.arr[0], point.arr[1] / param.arr[1] / param.arr[1], point.arr[2] / param.arr[2] / param.arr[2]));
	return (k0 * (k0 - 1) / k1);
}

double len_octahedron(t_vec point, t_vec param)
{
	double	m;
	t_vec	q;
	double	k;

	point = vec_fabs(point);
	m = point.arr[0] + point.arr[1] + point.arr[2] - param.arr[0];
	if (3.0 * point.arr[0] < m)
		q = point;
	else if (3.0 * point.arr[1] < m)
		q = new_vec3(point.arr[1], point.arr[2], point.arr[0]);
	else if (3.0 * point.arr[2] < m)
		q = new_vec3(point.arr[2], point.arr[0], point.arr[1]);
	else
		return (m * 0.57735027);
	k = clamp1(0.5 * (q.arr[2] -  q.arr[1] + param.arr[0]), 0.0, param.arr[0]);
	return (vec_len(new_vec3(q.arr[0], q.arr[1] - param.arr[0] + k, q.arr[2] - k)));
}

float maxcomp(t_vec p ) { return fmax(p.vec.x,fmax(p.vec.y,p.vec.z));}

double len_box(t_vec point, t_vec param)
{
	t_vec d;

	d = new_vec3(fabs(point.arr[0]), fabs(point.arr[1]), fabs(point.arr[2]));
	d = vec_sub(d, param);
	return(vec_len(vec_fmax(d, 0.0)) + fmin(fmax(d.arr[0], fmax(d.arr[1], d.arr[2])), 0));
}

float sdCross(t_vec point, t_vec param)
{
	param.arr[0] = 0;
	double da = maxcomp(vec_fabs(new_vec2(point.arr[0], point.arr[1])));
	double db = maxcomp(vec_fabs(new_vec2(point.arr[1], point.arr[2])));
	double dc = maxcomp(vec_fabs(new_vec2(point.arr[2], point.arr[0])));
	return fmin(da,fmin(db,dc))-1.0;
}

double len_box_fractal(t_vec point, t_vec param)
{
   double d = len_box(point, param);
   t_vec a = new_vec0();

   double s = 1.0;

	point = vec_sub(point, new_vec3(-1, -1, -1));
   for( int m=0; m<3; m++ )
   {
		a = vec_dotdec(point, s);
      	a.arr[0] = (fmod(a.arr[0], 2.0 )-1.0) * 3;
	  	a.arr[1] = (fmod(a.arr[1], 2.0 )-1.0) * 3;
	  	a.arr[2] = (fmod(a.arr[2], 2.0 )-1.0) * 3;
      
		s *= 3.0;
      double c = (sdCross(a, param))/s;
		d = fmax(d, -c);
   }

   return d;
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
        w.vec.z = point.vec.z +  -8.0*y*k4*(x4*x4 - 28.0*x4*x2*z2 + 70.0*x4*z4 - 28.0*x2*z2*z4 + z4*z4)*k1*k2;

        m = vec_dotvec(w,w);
		if( m > 256.0 )
            break;
    }

    //resColor = vec4(m, trap.yzw);

    return 0.25*log(m)*sqrt(m)/dz;
}
