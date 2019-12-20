/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter_5.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 11:18:47 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/12/16 11:43:39 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"
#include "perlin_noise.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#define NUM_OCTAVES 4

float noize(int x, int y)
{
    int n = x + y * 57;
    n = (n<<13) ^ n;
    return ( 1.0f - ( (n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) /
            1073741824.0f);
}

float smooth(float x, float y)
{
    float corners = (noize(x - 1, y - 1) + noize(x + 1, y - 1)+
         noize(x - 1, y + 1) + noize(x + 1, y + 1)) / 16;
    float sides   = ( noize(x-1, y)  +noize(x + 1, y)  +
         noize(x, y-1) + noize(x, y + 1) ) /  8;
    float center  =  noize(x, y) / 4;
    return (corners + sides + center);
}

float cosine_interpolate(float a, float b, float x)
{
    float ft = x * 3.1415927;
    float f = (1 - cosf(ft)) * 0.5;
    return(a*(1-f) + b*f);
}

float compile_noize(float x, float y)
{
    float int_X = (int)x;
      float fractional_X = x - int_X;
      float int_Y    = (int)y;
      float fractional_Y = y - int_Y;
     float v1 = smooth(int_X,     int_Y);
     float v2 = smooth(int_X + 1, int_Y);
     float v3 = smooth(int_X,     int_Y + 1);
     float v4 = smooth(int_X + 1, int_Y + 1);
      float i1 = cosine_interpolate(v1 , v2 , fractional_X);
      float i2 = cosine_interpolate(v3 , v4 , fractional_X);
      return cosine_interpolate(i1 , i2 , fractional_Y);
}

int     perlin_noize(float x, float y, float factor)
{
    float total;
    float persistence;
    float frequency;
    float amplitude;
    int i;
    
    i = 0;
    total = cosf(sqrtf(2))*3.14f;
    persistence = 0.5f;
    frequency = 0.25f;
     amplitude = 1;
    x += (factor);
    y += (factor);
    while (i<NUM_OCTAVES)
    {
       total += compile_noize(x * frequency, y * frequency) * amplitude;
       amplitude *= persistence;
       frequency *=2;
       i++;
    }
    total = fabsf(total);
    int res = total*255.0f;
    return (res);
}

void perlin(unsigned int **pixels)
{
    float factor;
    int x;
    int y;
    int color;

    srand(time(NULL));
    y = 0;
    while (y < 1200)
    {
        x = 0;
        while (x < 1200)
        {
            factor = (rand() % 10) / 10;
            color = perlin_noize(x, y, factor);
            color = 0xff << 24 | color << 16 | color << 8 | color;
            (*pixels)[x + y * 1200] = color;
            x++;
        }
        y++;
    }
}

t_texture		get_disruption(t_json *j, char *name)
{
	int				name_disruption;
	int				res;
	t_texture		disrupt;
	SDL_Surface		*serf;
	unsigned int *pixels;

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
	else if (name_disruption == 2)
	{
		serf = SDL_CreateRGBSurface(0, 1200, 1200, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
		pixels = serf->pixels;
		perlin(&pixels);
		SDL_SaveBMP(serf, "bmp.bmp");
		SDL_FreeSurface(serf);
		if (!(serf = SDL_LoadBMP("bmp.bmp")))
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
