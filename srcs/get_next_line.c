/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: kmeera-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:23:04 by kmeera-r          #+#    #+#             */
/*   Updated: 2018/11/29 16:23:07 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int				cpy_buff(t_fd_list *elem, char *buf, int i)
{
	char *s;

	s = elem->buff;
	if (!(elem->buff = ft_strjoin(elem->buff + i, buf)))
		return (0);
	if (s)
		free(s);
	return (1);
}

int				fd_clr(t_fd_list **lst, int fd)
{
	t_fd_list *first;
	t_fd_list *lst2;
	t_fd_list *lst3;

	first = *lst;
	lst3 = *lst;
	lst2 = NULL;
	while (lst3->fd != fd)
	{
		lst2 = lst3;
		lst3 = lst3->next;
	}
	if (lst2)
		lst2->next = lst3->next;
	else
		first = lst3->next;
	if (lst)
	{
		free(lst3->buff);
		free(lst3);
	}
	*lst = first;
	return (0);
}

int				ft_strccpy(int fd, char *buf, t_fd_list *elem, int *ret)
{
	while ((*ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[*ret] = '\0';
		if (!(cpy_buff(elem, buf, 0)))
			return (-1);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (0);
}

t_fd_list		*choose_fd(t_fd_list **lst, int fd)
{
	t_fd_list	*new_lst;

	if (!(*lst))
	{
		if (!(new_lst = (t_fd_list*)malloc(sizeof(t_fd_list))))
			return (NULL);
		new_lst->fd = fd;
		new_lst->start = 0;
		new_lst->next = NULL;
		new_lst->buff = ft_strdup("\0");
		*lst = new_lst;
		return (*lst);
	}
	if ((*lst)->fd == fd)
		return (*lst);
	return (choose_fd((&(*lst)->next), fd));
}

int				get_next_line(const int fd, char **line)
{
	char				buf[BUFF_SIZE + 1];
	static t_fd_list	*lst = NULL;
	int					i;
	t_fd_list			*elem;

	if (read(fd, buf, 0) < 0 || !line)
		return (-1);
	elem = choose_fd(&lst, fd);
	ft_strccpy(fd, buf, elem, &i);
	if (i < BUFF_SIZE && !ft_strlen(elem->buff))
		return (fd_clr(&lst, fd));
	i = 0;
	while ((elem->buff)[i] != '\n' && (elem->buff)[i] != '\0')
		i++;
	if (!(*line = ft_strndup(elem->buff, i)))
		i = 0;
	buf[0] = '\0';
	if (i < (int)ft_strlen(elem->buff))
	{
		if (!(cpy_buff(elem, buf, i + 1)))
			return (-1);
	}
	else
		ft_strclr(elem->buff);
=======
/*   By: bturcott <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:40:39 by bturcott          #+#    #+#             */
/*   Updated: 2018/12/15 17:41:45 by bturcott         ###   ########.fr       */
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
	if (elem->content == 0 || *elem->content == 0)
		return (0);
	elem->content = ft_strdupn(line, elem->content, '\n');
>>>>>>> 6d7e0dd41a3709cd3516e6fe739e83f359ca5907
	return (1);
}
