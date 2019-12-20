/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:18:47 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/12/20 18:29:02 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"
#include "perlin_noise.h"

t_texture		get_disruption(t_json *j, char *name)
{
	int				name_disruption;
	int				res;
	t_texture		disrupt;
	SDL_Surface		*serf;
	int x = 0, y = 0;

	disrupt.h = 1200;
	disrupt.w = 1200;
	disrupt.len_u = 1200;
	disrupt.len_v = 1200;
	name_disruption = query_attribute(j, name, &res).int_value;
	disrupt.texture = 0;
	if (res)
		return (disrupt);
	if (name_disruption == 0)
	{
		if (!(serf = SDL_LoadBMP("chess.bmp")))
			return (disrupt);
		disrupt.texture = serf->pixels;
		return (disrupt);
	}
	else if (name_disruption == 2)
	{
		disrupt.texture = ft_memalloc(sizeof(unsigned char) * 1200 * 1200 * 4);
		while (x < 1200)
		{
			y = 0;
			while (y < 4800)
			{
				disrupt.texture[y + x * 4800] =  25600 * noise1(y / 4800);
				y++;
				disrupt.texture[y + x * 4800] = disrupt.texture[y + x * 4800 - 1];
				y++;
				disrupt.texture[y + x * 4800] = disrupt.texture[y + x * 4800 - 1];
				y++;
				disrupt.texture[y + x * 4800] = disrupt.texture[y + x * 4800 - 1];
				y++;
			}
			x++;
		}
		return (disrupt);
	}
	return (disrupt);
}

t_texture		get_texture(t_json *j, char *name)
{
	int			res;
	SDL_Surface	*serf;
	t_texture	tex;
	t_json		*json;
	char		*path;

	tex.texture = NULL;
	json = (t_json*)query_attribute(j, name, &res).json_value;
	if (res)
		return (tex);
	path = query_attribute(json, "path", &res).string_value;
	if (res)
		return (tex);
	if (!(serf = SDL_LoadBMP(path)))
		return (tex);
	tex.texture = serf->pixels;
	tex.h = serf->h;
	tex.w = serf->w;
	tex.len_u = query_attribute(json, "len_u", &res).float_value;
	if (res)
		tex.len_u = tex.h;
	tex.len_v = query_attribute(json, "len_v", &res).float_value;
	if (res)
		tex.len_v = tex.w;
	return (tex);
}

int				check_plane(char *name)
{
	return (!ft_strncmp(name, "plane", 5));
}

void			get_restriction2(t_restr *restr)
{
	t_json *j;

	j = (t_json*)query_attribute(restr->json,\
	restr->names[restr->n], &restr->res).json_value;
	if (!restr->res)
	{
		restr->r[restr->n].dislocation = get_vec(query_attribute(j,\
							"dislocation", &restr->res).json_value);
		if (restr->res)
			restr->r[restr->n].dislocation = new_vec0();
		restr->r[restr->n].norm = vec_norm(get_vec(query_attribute(j,\
								"norm", &restr->res).json_value));
		if (restr->res)
			restr->r[restr->n].norm = new_vec0();
	}
}

t_restriction	*get_restriction(t_json *j, int *ns_p)
{
	t_restr		restr;

	restr.json = (t_json*)query_attribute(j,\
				"restriction", &restr.res).json_value;
	if (restr.res)
		return (NULL);
	restr.res = gate_names_obj(restr.json, &restr.names, check_plane);
	if (!(restr.r = ft_memalloc(sizeof(t_restriction) * restr.res)))
		return (NULL);
	restr.n = restr.res;
	*ns_p = restr.res;
	while (restr.n--)
	{
		get_restriction2(&restr);
	}
	return (restr.r);
}

void			get_obj2(t_json *json, t_obj *object)
{
	int			res;
	double		angle;
	t_vec		rotvec;

	object->transparency = query_attribute(json,\
							"transparency", &res).float_value;
	if (res)
		object->transparency = 0;
	object->frequency = query_attribute(json, "frequency", &res).float_value;
	if (res)
		object->frequency = 0;
	object->amplitude = query_attribute(json, "amplitude", &res).float_value;
	if (res)
		object->amplitude = 0;
	object->color = get_vec(query_attribute(json, "color", &res).json_value);
	if (res)
		object->color = new_vec0();
	angle = query_attribute(json, "angle", &res).float_value;
	if (res)
		angle = 0;
	rotvec = get_vec(query_attribute(json, "rot_vec", &res).json_value);
	if (res)
		rotvec = new_vec0();
	object->rot_quat = create_quat(vec_norm(rotvec), angle);
}
