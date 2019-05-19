/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:49:37 by bturcott          #+#    #+#             */
/*   Updated: 2019/05/19 19:54:22 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"

t_json *create_json_obj()
{
	t_json *obj;

	if (!(obj = (t_json *)malloc(sizeof(t_json))))
		return (NULL);
	if (!(obj->key = (char **)malloc(sizeof(char *) * (MAX_FIELDS + 1))))
		return (NULL);
	if (!(obj->value = malloc(sizeof(void *) * (MAX_FIELDS + 1))))
		return (NULL);
	return(obj);
}


char *parse_key(char *file, int pos)
{
	int quotes;
	
	quotes = pos;
	while (file[pos])
	{
		if (file[pos++] == '"')
			{
				while (file[pos] && file[pos] != '"' && file[pos - 1] != '\\')
					pos++;
				return (ft_strsub(file, quotes, pos));
			}
		pos++;
	}
}

void *parse_value(char *file, int pos)
{
	while (file[pos] && file[pos] != '"' || file[pos] != '[' 
	|| file[pos] != '{' || !ft_isdigit(file[pos]))
		pos++;
	if (file[pos] == '"')
		return (parse_key(file, pos));
	else if (file[pos++] == '{')
		return NULL;
	else if (ft_isdigit(file[pos]))
		return(ft_atoi(file + pos));
	
}
t_json *make_json(char *file, int pos)
{
	t_json	*obj;
	int		i;

	obj = create_json_obj();
	i = -1;
	while (file[pos] && ++i < MAX_FIELDS)
	{
		obj->key[i] = parse_key(file, pos);
		while (file[pos] != ':')
			pos++;
		if (!(obj->value[i] = parse_value(file, pos)))
			obj->value[i] = make_json(file, file - ft_strchr(file + pos, '{') + 1);
		while (file[pos] != ',')
			pos++;
	}
}

char *read_file(int fd){
	
	char *file;
	char *temp;
	int i;
	
	i = 0;
	while ((temp = get_next_line(fd, &temp)))
	{
		file = ft_strjoin(file, temp);
		free(temp);
	}
	while (file[i] && file[i] != '{')
		i++;
	temp = ft_strsub(file, i, ft_strlen(file) - i);
	free(file);
	return (temp);
}

t_list *parse_json(char *config_file)
{
	int fd;
	t_list *json;
	t_json *obj;
	t_list *tmp;
	char 	*file;

	fd = fopen(config_file, O_RDONLY);
	if (fd == -1 || fd == 0)
	{   
		ft_putendl("Missing config file...");
		exit(0);
	}
	file = read_file(fd);
	close(fd);
	while (obj = make_json(file, 0))
	{
		tmp = ft_lstnew((void *)obj, sizeof(obj));
		ft_lstpushback(json, tmp);
	}
	return (json);
}