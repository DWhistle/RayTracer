/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 17:40:39 by bturcott          #+#    #+#             */
/*   Updated: 2019/11/09 16:10:23 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"
#include "libft.h"

static int	ret_line(char **line, char **lines, int length)
{
	int		len;

	if (!lines)
		return (-1);
	if (!line)
	{
		ft_strdel(lines);
		*lines = NULL;
		return (-1);
	}
	ft_strclr(*line);
	if (**lines == 0)
		return (0);
	*line = ft_strsub(*lines, 0, length);
	len = ft_strlen(*lines);
	ft_memmove(*lines, *lines + length + 1, len - length);
	(*lines)[len - length] = 0;
	return (1);
}

static int	ft_read_line(const int fd, char **lines)
{
	char	buf[BUFF_SIZE + 1];
	char	*temp;
	int		ret;

	if (!*lines)
		*lines = ft_strnew(0);
	if (fd < 0)
	{
		ft_strclr(*lines);
		return (-1);
	}
	ret = read(fd, buf, BUFF_SIZE);
	if (ret >= 0)
	{
		buf[ret] = 0;
		if (*lines)
		{
			temp = ft_strjoin(*lines, buf);
			ft_strdel(lines);
			*lines = temp;
		}
	}
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	int			ret;
	char		*linebreak;
	static char	*lines = NULL;

	if (line)
		*line = "";
	if (lines && *lines)
	{
		if ((linebreak = ft_strchr(lines, '\n')))
			return (ret_line(line, &lines, linebreak - lines));
	}
	ret = ft_read_line(fd, &lines);
	if (ret == 0)
		return (ret_line(line, &lines, ft_strlen(lines)));
	else if (ret < 0)
		return (-1);
	while (!(linebreak = ft_strchr(lines, '\n')))
	{
		ret = ft_read_line(fd, &lines);
		if (ret == 0)
			return (ret_line(line, &lines, ft_strlen(lines)));
		else if (ret < 0)
			return (-1);
	}
	return (ret_line(line, &lines, linebreak - lines));
}
