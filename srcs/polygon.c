#include "ray_render.h"

double	triangle_area(t_vec f, t_vec s, t_vec th)
{
    return(vec_sqrdist(vec_mul(vec_sub(s, f), vec_sub(th, f))) / 2);
}

t_segment closest_segment(t_polygon polygon, t_vec point)
{
	int			counter;
	int			p;
	t_segment	segment;

	segment.a = polygon.points[0];
	counter = 0;
	p = 0;
	while (counter++ != polygon.number_point)
		if(vec_sqrdist(segment.a) > vec_sqrdist(polygon.points[counter]))
		{
			segment.a = polygon.points[counter];
			p = counter;
		}
	if(!p)
		segment.b = polygon.points[1];
	else
		segment.b = polygon.points[0];
	counter = 0;
	while (counter++ != polygon.number_point)
		if(vec_sqrdist(segment.b) > vec_sqrdist(polygon.points[counter]) && counter != p)
			segment.b = polygon.points[counter];
	return (segment);
}

int		point_in_polygon(t_polygon polygon, t_vec point)
{
	double	s1;
	double	s2;
    int		counter;

	counter = 0;
	s1 = 0;
	while (counter + 1 != polygon.number_point)
	{
		s1 += triangle_area(point, polygon.points[counter], polygon.points[counter + 1]);
		counter++;
	}
	counter = 0;
	s2 = 0;
	while (counter + 1 != polygon.number_point)
	{
		s2 += triangle_area(polygon.points[0], polygon.points[counter], polygon.points[counter + 1]);
		counter++;
	}
	return (s1 > s2);
}

double	len_segment(t_segment segment, t_vec point)
{
	double	sina;
	t_vec	vec1;
	t_vec	vec2;

	vec1 = vec_sub(segment.a, segment.b);
	vec2 = vec_sub(segment.a, point);

	sina = vec_dotvec(vec_sub(segment.a, segment.b), vec_sub(segment.a, point));
}

