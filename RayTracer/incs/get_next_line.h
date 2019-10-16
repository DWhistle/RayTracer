/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 22:44:10 by kmeera-r          #+#    #+#             */
/*   Updated: 2019/09/26 18:58:40 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct	s_fd_list
{
	int					fd;
	int					start;
	char				*buff;
	struct s_fd_list	*next;
	struct s_fd_list	*previous;
}				t_fd_list;

# define BUFF_SIZE 4096

int				get_next_line(int const fd, char **line);

#endif
