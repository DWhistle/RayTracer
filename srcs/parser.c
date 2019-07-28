/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:48:30 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/25 20:33:11 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_json		*create_json_obj(void)
{
	t_json *obj;

	if (!(obj = (t_json *)malloc(sizeof(t_json))))
		return (NULL);
	if (!(obj->key = (char **)malloc(sizeof(char *) * (MAX_FIELDS + 1))))
		return (NULL);
	if (!(obj->value = malloc(sizeof(t_values) * (MAX_FIELDS + 1))))
		return (NULL);
	if (!(obj->type = (int *)malloc(sizeof(int) * (MAX_FIELDS + 1))))
		return (NULL);
	obj->key[MAX_FIELDS] = NULL;
	return (obj);
}

int			make_json(t_parser *json, t_json *obj)
{
	int i;

	i = 0;
	while (json->f[json->i] && json->f[json->i] != '}')
	{
		if (i > MAX_FIELDS)
			return (-1);
		parse_key(json, &obj->key[i]);
		while (json->f[json->i] && json->f[json->i] != ':')
			json->i++;
		if (parse_value(json, obj->value, &obj->type, i) == -1)
			return (1);
		while (json->f[json->i] && json->f[json->i] != ','
		&& json->f[json->i] != '}')
			json->i++;
		i++;
	}
	json->i += (json->f[json->i]) ? 1 : 0;
	obj->type[i] = 0;
	obj->key[i] = NULL;
	return (1);
}

t_list		*json_operator(t_parser *json)
{
	t_json *obj;

	while (json->f[json->i])
	{
		if (json->f[json->i] == '{')
		{
			json->i++;
			if (!(obj = create_json_obj()))
				return (NULL);
			make_json(json, obj);
			ft_lstadd(&json->objects, ft_lstnew((void *)obj, sizeof(t_json)));
		}
		json->i += (json->f[json->i]) ? 1 : 0;
	}
	return (json->objects);
}

char		*read_file(int fd)
{
	char	*file;
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	temp2 = ft_strdup("\0");
	while (get_next_line(fd, &temp))
	{
		file = ft_strjoin(temp2, temp);
		free(temp2);
		free(temp);
		temp2 = file;
	}
	return (file);
}

t_list		*parse_json(char *config_file)
{
	int			fd;
	t_parser	*json;

	fd = open(config_file, O_RDONLY);
	if (fd == -1 || fd == 0)
	{
		ft_putendl("Missing json file...");
		exit(0);
	}
	if (!(json = ft_memalloc(sizeof(t_parser))))
		return (NULL);
	if (!(json->f = read_file(fd)))
		return (NULL);
	json->i = 0;
	json->objects = NULL;
	close(fd);
	return (json_operator(json));
}
