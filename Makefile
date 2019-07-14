	# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/20 19:22:42 by hgreenfe          #+#    #+#              #
#    Updated: 2019/05/27 16:56:16 by kmeera-r         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# used variables
NAME = RT
MY_DIR = $(shell pwd)
SRCDIR = srcs/
OBJDIR = objs/
INCDIR1 = incs/
LIBDIR = libs/libft
LIBUIDIR = libs/libui
INCDIR2 = $(LIBUIDIR)/incs
SDLDIR = $(LIBUIDIR)/SDL/lib
LIBS = ft ui
 #SDL2_image
# used applications

CC = gcc
CCFLAGS = -g -Wall -Wextra -Werror -pedantic-errors -I $(INCDIR1) -I $(INCDIR2) -O
RM = rm
RMFLAGS = -rf

#used directories and files

FILES := main \
		 raymarching \
		 vec_mul \
		 vec_sum \
		 vector \
		 ray_tracing \
		 antialiasing \
		 len_obj \
		 ft_opencl_files \
		 ft_opencl_func \
		 ft_opencl_params \
		 quaternion_1 \
		 quaternion_2 \
		 light \
		 reflaction \
		 transparency \
		 parser \
		 get_next_line \
		 #converter


HEADERS = $(INCDIR1)/SDL2/SDL.h $(INCDIR1)/ft_libui.h $(INCDIR1)/ft_window.h

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))
FULL_SRCS = $(addprefix $(SRCDIR), $(SRCS))
FULL_OBJS = $(addprefix $(OBJDIR), $(OBJS))
FULL_LIBS = $(addprefix -l, $(LIBS))
FRAMEWORK = -framework OpenGL -framework Cocoa -framework OpenCL
#  -framework iconv
LIBFLAGS = -L$(LIBDIR) -lft -L$(LIBUIDIR) -lui -L$(SDLDIR) -lSDL2

# vpath %.c $(SRCDIR)/
# vpath %.o $(OBJDIR)/

.PHONY:  all re clean fclean $(LIBDIR)

all: $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBDIR): $(OBJDIR)
	make -C $(LIBDIR)
	make -C $(LIBUIDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CCFLAGS) -c -o $@ $<


$(NAME):  $(LIBDIR) $(SDL) $(FULL_OBJS)
	$(CC) $(CCFLAGS) -o $(NAME) $(FRAMEWORK) $(LIBFLAGS) $(FULL_OBJS)

clean:
	make -C $(LIBDIR) clean
	make -C $(LIBUIDIR) clean
	$(RM) $(RMFLAGS) $(FULL_OBJS)

fclean: clean
	make -C $(LIBDIR) fclean
	make -C $(LIBUIDIR) fclean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all
