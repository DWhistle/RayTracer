/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:49:37 by bturcott          #+#    #+#             */
/*   Updated: 2019/05/19 18:02:08 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parser.h"

t_json *create_json_obj(){
	t_json *obj;

	if (!(obj = (t_json *)malloc(sizeof(t_json))))
		return (NULL);
	if (!(obj->key = (char **)malloc(sizeof(char *) * (MAX_FIELDS + 1))))
		return (NULL);
	if (!(obj->value = malloc(sizeof(void *) * (MAX_FIELDS + 1))))
		return (NULL);
	return(obj);
}

t_json *make_json(char *file, int pos)
{
	t_json	*obj;
	int		i;
	int		quotes;

	obj = create_json_obj();
	i = -1;
	while (file[pos] && ++i < MAX_FIELDS){
		if (file[pos++] == "\"" && (quotes = pos))
		{
			while (file[pos] && file[pos] != "\"")
				pos++;
			obj->key[i] = ft_strsub(file, quotes, pos);
			while (file[pos] != "\"")
				pos++;
			quotes = pos;
		}
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
	return (file);
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