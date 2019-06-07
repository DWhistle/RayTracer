/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_opencl_files.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 21:59:14 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/06/06 01:04:01 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_opencl_func.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

char		*ft_get_cl_name(const char *name, char *dirname)
{
	char	*ret;
	char	*base;

	base = ft_strjoin(dirname, name);
	ret = ft_strjoin(base, ".cl");
	ft_strdel(&base);
	return (ret);
}

size_t		text_from_file(const char *filename, char **file_content)
{
	int		fd;
	ssize_t	ret;
	char	buf[BUFFER_SIZE];
	char	*temp;
	size_t	filesize;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	filesize = 0;
	ret = 1;
	*file_content = ft_strnew(0);
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret < 0)
			return (0);
		temp = ft_strjoin(*file_content, buf);
		free(*file_content);
		*file_content = temp;
		filesize += ret;
	}
	return (filesize);
}
