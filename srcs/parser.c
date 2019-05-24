/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:49:37 by bturcott          #+#    #+#             */
/*   Updated: 2019/05/24 19:07:03 by hgreenfe         ###   ########.fr       */
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
	if (!(obj->type = (char *)malloc(sizeof(char) * (MAX_FIELDS + 1))))
		return (NULL);
	return(obj);
}


char *parse_key(char *file, int pos)
{
	int quotes;
	
	quotes = 0;
	while (file[pos])
	{
		if (file[pos] == '"')
			{
				++pos;
				while (file[pos + quotes] && file[pos + quotes] != '"')
					quotes++;
				return (ft_strsub(file, pos, quotes));
			}
		pos++;
	}
	return (NULL);
}

int *parse_array(char *file, int pos)
{
	int mem_pos;
	int len;
	int *arr;

	len = 2;
	mem_pos = pos - 1;
	while (file[++mem_pos] != ']')
		if (file[mem_pos] == ',')
			len++;
	arr = (int *)malloc(sizeof(int) * len);
	len = -1;
	while (pos <= mem_pos)
	{
		if (ft_isdigit(file[pos]))
		{
			arr[++len] = ft_atoi(file + pos);
			while (ft_isdigit(file[pos]))
				pos++;
		}
		pos++;
	}
	return (arr);
}

int parse_value(char *file, int pos, t_json *obj, int i)
{
	int *val;
	
	while (file[pos] && file[pos] != '"' && file[pos] != '['
	&& file[pos] != '{' && !ft_isdigit(file[pos]))
		pos++;
	if (file[pos] == '[' && (obj->type[i] = 'a'))
		obj->value[i] = parse_array(file, pos);
	else if (file[pos] == '"' && (obj->type[i] = 's'))
		obj->value[i] = parse_key(file, pos);
	else if (ft_isdigit(file[pos]) && (obj->type[i] = 'i'))
	{
		obj->value[i] = (int *)malloc(sizeof(int));
		val = (int *)obj->value[i];
		val[0] = ft_atoi(file + pos);
	}
	else
		return (-1);
	return(0);
}

int make_json(char *file, int pos, t_json *obj)
{
	int		i;
	
	if (file[pos] == '}')
		return 0;
	obj = create_json_obj();
	i = -1;
	while (file[pos] && file[pos] != '}' && ++i < MAX_FIELDS)
	{
		obj->key[i] = parse_key(file, pos);
		while (file[pos] && file[pos] != ':')
			pos++;
		parse_value(file, ++pos, obj, i);
		while (file[pos] && file[pos] != ',' && file[pos] != '}')
			pos++;
		while (file[pos] && file[pos] != '"' && file[pos] != '}')
			pos++;
		if (file[pos] == '}')
			return (pos + 1);
		else if (file[pos] == 0)
			return (0);
	}
	return (0);
}

char *read_file(int fd){
	
	char *file;
	char *temp;
	char *temp2;
	int i;
	
	i = 0;
	temp2 = ft_strdup("\0");
	while (get_next_line(fd, &temp))
	{
		file = ft_strjoin(temp2, temp);
		free(temp2);
		free(temp);
		temp2 = file;
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
	t_json obj;
	int pos;
	char 	*file;

	fd = open(config_file, O_RDONLY);
	pos = 0;
	if (fd == -1 || fd == 0)
	{   
		ft_putendl("Missing config file...");
		exit(0);
	}
	file = read_file(fd);
	close(fd);
	while ((pos = make_json(file, pos, &obj)))
	{
		ft_lstadd(&json, ft_lstnew((void **)&obj, sizeof(t_json)));
	}
	return (json);
}


int main(int ac, char **av)
{
	t_list *json = parse_json(av[1]);
}