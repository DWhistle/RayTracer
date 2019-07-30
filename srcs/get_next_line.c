/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:40:39 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

t_list		*find_n_alloc(const int fd, t_list **begin)
{
	t_list *check;
	t_list *new;

	new = NULL;
	check = *begin;
	if (*begin)
		while (check)
		{
			if ((int)check->content_size == fd)
				return (check);
			if (!check->next)
				break ;
			check = check->next;
		}
	new = ft_lstnew("\0", (int)fd);
	new->next = NULL;
	if (*begin)
		check->next = new;
	else
		*begin = new;
	return (new);
}

char		*ft_newline(char *src, int i, char **line)
{
	int		c;
	int		d;
	char	*cont;

	c = 0;
	d = i;
	if (!(*line = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (src[d])
		d++;
	if (!(cont = (char *)malloc(sizeof(char) * (d - i) + 1)))
		return (NULL);
	while (c < i)
	{
		line[0][c] = src[c];
		c++;
	}
	line[0][c++] = 0;
	i = 0;
	while (c < d)
		cont[i++] = src[c++];
	cont[i] = 0;
	free(src);
	return (cont);
}

char		*ft_strdupn(char **line, char *src, char m)
{
	int i;
	int l;

	i = 0;
	l = 0;
	while (src[i] && src[i] != m)
		i++;
	while (src[l])
		l++;
	if (i != l)
		src = ft_newline(src, i, line);
	else
	{
		if (!(*line = (char *)malloc(sizeof(char) * (i + 1))))
			return (NULL);
		l = -1;
		while (i > ++l)
			line[0][l] = src[l];
		line[0][l] = 0;
		free(src);
		return (NULL);
	}
	return (src);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*begin;
	t_list			*elem;
	char			*temp;
	int				i;

	i = 0;
	elem = NULL;
	temp = NULL;
	if (read(fd, temp, 0) < 0 || fd == -1 || !line)
		return (-1);
	if (!(temp = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1))))
		return (0);
	elem = find_n_alloc(fd, &begin);
	if (elem->content == 0)
		return (0);
	while (!(ft_strchr(elem->content, '\n')) && (i = read(fd, temp, BUFF_SIZE)))
	{
		temp[i] = 0;
		elem->content = ft_strjoin(elem->content, temp);
	}
	free(temp);
	if (elem->content == 0)
		return (0);
	elem->content = ft_strdupn(line, elem->content, '\n');
	return (1);
}
