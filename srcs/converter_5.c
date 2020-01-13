/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:18:47 by kmeera-r          #+#    #+#             */
/*   Updated: 2020/01/13 20:12:26 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"
#include "perlin_noise.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NUM_OCTAVES 4

t_texture		get_disruption(t_json *j, char *name)
{
	int				name_disruption;
	int				res;
	t_texture		disrupt;
	SDL_Surface		*serf;

	disrupt.h = 1200;
	disrupt.w = 1200;
	disrupt.len_u = 120;
	disrupt.len_v = 120;
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
