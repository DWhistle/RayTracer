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
SRCDIR = srcs/
OBJDIR = objs/
INCDIR1 = incs/
INCDIR2 = libs/SDL/include
LIBDIR = libs/libft
SDLDIR = libs/SDL/lib
SDLIMGDIR = libs/SDL/SDL2_image/.libs
LIBS = ft SDL2 SDL2_image
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
		 path_tracing \
		 ray_tracing \
		 reflaction \
		 antialiasing \
		 len_obj


HEADERS = $(INCDIR1)/SDL2/SDL.h $(INCDIR1)/ft_libui.h $(INCDIR1)/ft_window.h

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))
FULL_SRCS = $(addprefix $(SRCDIR), $(SRCS))
FULL_OBJS = $(addprefix $(OBJDIR), $(OBJS))
FULL_LIBS = $(addprefix -l, $(LIBS))
FRAMEWORK = -framework OpenGL -framework Cocoa
#  -framework iconv
LIBFLAGS = -L$(LIBDIR) -lft -L $(SDLDIR) -lSDL2  -L $(SDLIMGDIR) -lSDL2_image
PATH_SDL = $(addsuffix /libs/SDL, $(shell pwd))
SDL =  $(PATH_SDL)/SDL2/build

# vpath %.c $(SRCDIR)/
# vpath %.o $(OBJDIR)/

.PHONY:  all re clean fclean $(LIBDIR)

all: $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(LIBDIR): $(OBJDIR)
	make -C $(LIBDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(SDL):
	cd $(PATH_SDL)/SDL2; ./configure --prefix=$(PATH_SDL)
	make -sC $(PATH_SDL)/SDL2 install
	cd $(PATH_SDL)/SDL2_image; ./configure --prefix=$(PATH_SDL) --with-sdl-prefix=$(PATH_SDL)
	make -sC $(PATH_SDL)/SDL2_image install

$(NAME):  $(LIBDIR) $(SDL) $(FULL_OBJS)
	$(CC) $(CCFLAGS) -o $(NAME) $(FRAMEWORK) $(LIBFLAGS) $(FULL_OBJS)

clean: clean_sdl
	make -C $(LIBDIR) clean
	$(RM) $(RMFLAGS) $(FULL_OBJS)

clean_sdl:
	make -C $(PATH_SDL)/SDL2 clean
	make -C $(PATH_SDL)/SDL2_image clean
	
fclean: clean
	make -C $(LIBDIR) fclean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all
