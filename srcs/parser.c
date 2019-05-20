/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:49:37 by bturcott          #+#    #+#             */
/*   Updated: 2019/05/20 17:10:02 by bturcott         ###   ########.fr       */
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
	
	quotes = 0;
	while (file[pos])
	{
		if (file[pos] == '"')
			{
				++pos;
				printf("%d\n", pos);
				while (file[pos + quotes] && file[pos + quotes] != '"')
					quotes++;
				printf("quotes %d pos == %d\n", quotes, pos);
				return (ft_strsub(file, pos, quotes));
			}
		pos++;
	}
	return (NULL);
}

void *parse_value(char *file, int pos)
{
	while (file[pos] && file[pos] != '"' && file[pos] != '[' 
	&& file[pos] != '{' && !ft_isdigit(file[pos]))
		pos++;
	printf("%c\n", file[pos + 1]);
	if (file[pos] == '"')
		return (parse_key(file, pos));
	else if (ft_isdigit(file[pos]))
		return(ft_atoi(file + pos));
	else
		return (NULL);
}

t_json *make_json(char *file, int pos, t_json *obj)
{
	int		i;
	
	if (file[pos] == '}')
		return NULL;
	obj = create_json_obj();
	i = -1;
	while (file[pos] && file[pos] != '}' && ++i < MAX_FIELDS)
	{
		printf("position before key %d\n", pos);
		obj->key[i] = parse_key(file, pos);
		printf("key == %s     pos == %d\n", obj->key[i], pos);
		while (file[pos] && file[pos] != ':')
			pos++;
		obj->value[i] = parse_value(file, ++pos);
		while (file[pos] && file[pos] != ',')
			pos++;
		printf("val == %d     pos == %d\n", obj->value[i], pos);	
		while (file[pos] && file[pos] != '"' && file[pos] != '}')
			pos++;
		if (file[pos] == '}')
			return (pos + 1);
		else if (file[pos] == 0)
			return (0);
		printf("%c\n", file[pos]);
	}
	return (pos);
}

char *read_file(int fd){
	
	char *file;
	char *temp;
	int i;
	
	i = 0;
	while (get_next_line(fd, &temp))
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
	printf("1\n");
	while ((pos = make_json(file, pos, obj)))
	{
		ft_lstpushback(json, ft_lstnew((void *)obj, sizeof(obj)));
		printf("list");
	}
	return (json);
}


int main(int ac, char **av)
{
	printf("%s\n", av[1]);
	t_list *json = parse_json(av[1]);
}