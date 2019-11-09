# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 19:22:42 by hgreenfe          #+#    #+#              #
#    Updated: 2019/09/28 11:59:04 by hgreenfe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCDIR = .
INCDIR = includes
CC = gcc
CCFLAGS = -g -Wall -Wextra -Werror -c -I $(INCDIR)
MAINS = mains

FILES =	$(SRCDIR)/ft_memset.c \
	$(SRCDIR)/ft_bzero.c \
	$(SRCDIR)/ft_strnew.c \
	$(SRCDIR)/ft_memcpy.c \
	$(SRCDIR)/ft_memccpy.c \
	$(SRCDIR)/ft_memmove.c \
	$(SRCDIR)/ft_memchr.c \
	$(SRCDIR)/ft_memcmp.c \
	$(SRCDIR)/ft_strlen.c \
	$(SRCDIR)/ft_strdup.c \
	$(SRCDIR)/ft_strndup.c \
	$(SRCDIR)/ft_strcpy.c \
	$(SRCDIR)/ft_strncpy.c \
	$(SRCDIR)/ft_strcat.c \
	$(SRCDIR)/ft_strncat.c \
	$(SRCDIR)/ft_strlcat.c \
	$(SRCDIR)/ft_strchr.c \
	$(SRCDIR)/ft_strrchr.c \
	$(SRCDIR)/ft_strstr.c \
	$(SRCDIR)/ft_strnstr.c \
	$(SRCDIR)/ft_strcmp.c \
	$(SRCDIR)/ft_strncmp.c \
	$(SRCDIR)/ft_atoi.c \
	$(SRCDIR)/ft_atoibase.c \
	$(SRCDIR)/ft_isalpha.c \
	$(SRCDIR)/ft_isdigit.c \
	$(SRCDIR)/ft_isalnum.c \
	$(SRCDIR)/ft_isascii.c \
	$(SRCDIR)/ft_isprint.c \
	$(SRCDIR)/ft_toupper.c \
	$(SRCDIR)/ft_tolower.c \
	$(SRCDIR)/ft_memalloc.c \
	$(SRCDIR)/ft_memdel.c \
	$(SRCDIR)/ft_strdel.c \
	$(SRCDIR)/ft_strclr.c \
	$(SRCDIR)/ft_striter.c \
	$(SRCDIR)/ft_striteri.c \
	$(SRCDIR)/ft_strmap.c \
	$(SRCDIR)/ft_strmapi.c \
	$(SRCDIR)/ft_strequ.c \
	$(SRCDIR)/ft_strnequ.c \
	$(SRCDIR)/ft_strsub.c \
	$(SRCDIR)/ft_strjoin.c \
	$(SRCDIR)/ft_strtrim.c \
	$(SRCDIR)/ft_strsplit.c \
	$(SRCDIR)/ft_itoa.c \
	$(SRCDIR)/ft_putchar.c \
	$(SRCDIR)/ft_putstr.c \
	$(SRCDIR)/ft_putendl.c \
	$(SRCDIR)/ft_putnbr.c \
	$(SRCDIR)/ft_putchar_fd.c \
	$(SRCDIR)/ft_putstr_fd.c \
	$(SRCDIR)/ft_putendl_fd.c \
	$(SRCDIR)/ft_putnbr_fd.c \
	$(SRCDIR)/ft_lstadd.c \
	$(SRCDIR)/ft_lstdel.c \
	$(SRCDIR)/ft_lstdelone.c \
	$(SRCDIR)/ft_lstiter.c \
	$(SRCDIR)/ft_lstmap.c \
	$(SRCDIR)/ft_lstnew.c \
	$(SRCDIR)/ft_lstpushback.c \
	$(SRCDIR)/ft_lstpushfront.c \
	$(SRCDIR)/ft_lstpopback.c \
	$(SRCDIR)/ft_lstpopfront.c \
	$(SRCDIR)/ft_strswap.c \
	$(SRCDIR)/ft_remalloc.c \
	$(SRCDIR)/ft_power.c

OBJ = $(FILES:.c=.o)

.c.o:
	$(CC) $(CCFLAGS) $^

AR = ar -rsc
RM = rm
RMFLAGS = -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CCFLAGS) $(FILES)
	$(AR) $(NAME) $(OBJ)

test: 
	$(CC) $(CCFLAGS) -L. -lft $(SRCDIR)/main.c

clean:
	$(RM) $(RMFLAGS) $(OBJ)

fclean: clean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all
