/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 19:11:20 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/05/25 19:11:20 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_point_data raymarching(t_scene objs, t_vec vec, t_accuracy accuracy, t_vec point)
{
	double r;
	int counter;
	t_point_data point_data;
	t_vec next_point;

	next_point = point;
	while (accuracy.depth_march-- && vec_len(vec_sub(point, next_point)) < accuracy.max_dist)
	{
		r = -1;
		counter = objs.number_objs;
		while (counter--)
		{
			r = update_r(r, objs.objs[counter], next_point, objs);
			if (r < accuracy.delta && r != -1)
			{
				point_data.norm = get_normal(next_point, objs.objs[counter]);
				point_data.obj = objs.objs + counter;
				point_data.point = next_point;
				return (point_data);
			}
		}
		next_point = vec_sum(next_point, vec_dotdec(vec, r));
	}
	point_data.norm = new_vec0();
	point_data.obj = 0;
	point_data.point = new_vec0();
	return (point_data);
}

t_vec   ray_render(t_scene scene, t_vec point, t_accuracy accuracy)

{
	int				depth_ref;
	t_point_data	point_data;
	t_point_data	*points;
	t_vec			color;
	t_vec			vec;

	vec = vec_norm(vec_sub(point, scene.cam));
	point_data = path_tracing(scene, vec, accuracy, scene.cam);

	if (point_data.obj)
	{
		points = (t_point_data*)ft_memalloc(sizeof(t_point_data) * (accuracy.depth_ref + 1));
		points[0] = point_data;
		depth_ref = 0;
		while ((accuracy.depth_ref > depth_ref++) && (point_data.obj) && (point_data.obj->reflection))
		{
			scene.ignore = point_data.obj;
			point_data = path_tracing(scene, get_ref_vec(point_data, vec), accuracy, point_data.point);
			points[depth_ref] = point_data;
		}
		points[depth_ref].obj = 0;;
		color = get_ref_color(points);
		free(points);
		return(color);
	}
	return (new_vec0());
}
