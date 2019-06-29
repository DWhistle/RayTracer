/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
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
	return (1);
}
