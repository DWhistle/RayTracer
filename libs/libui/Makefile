# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/06/17 20:30:06 by hgreenfe          #+#    #+#              #
#    Updated: 2019/07/14 15:03:16 by hgreenfe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# used variables
NAME = ui

SRCDIR = srcs/

OBJDIR = objs/

LIBUIDIR = ./
LIBDIR = ../libft/

INCDIR1 = incs/
INCSDL = $(LIBUIDIR)/SDL/include

PATH_SDL := $(addsuffix /SDL, $(shell pwd))
SDL :=  $(PATH_SDL)/SDL2/build/.libs

# used applications
CC = gcc
CCFLAGS = -Ofast -Wall -Wextra -Werror -pedantic-errors -I $(LIBDIR) -I $(INCDIR1) -I $(INCSDL)
AR = ar
ARFLAGS = -rs
RM = rm
RMFLAGS = -rf

#used files
FILES := ft_window \
         ft_events \
         libui_defaults \
         ft_event_func \
         ft_control \
         ft_control_destructors \
         ft_set_window_params \
         ft_drawable \
         ft_controlevent \
         ft_libui \
         redraw_functions \
         ft_event_params \
         ft_get_window_params \
         ft_set_window_custom_params \
         ft_get_window_custom_params \
         ft_get_control_params \
         ft_set_control_params \
         ft_event_additional \
		 ft_cursor \
		 ft_primitives \
		 ft_blendings 

HEADERS = $(INCDIR1)/SDL2/SDL.h $(INCDIR1)/ft_libui.h

SRCS = $(addsuffix .c, $(FILES))
OBJS = $(addsuffix .o, $(FILES))

FULL_SRCS = $(addprefix $(SRCDIR), $(SRCS))
FULL_OBJS = $(addprefix $(OBJDIR), $(OBJS))

FRAMEWORK = -framework OpenGL -framework Cocoa
#  -framework iconv

LIBFLAGS = -L$(LIBDIR) -lft -L $(SDL) -lSDL2
# -L $(LIBSDIR)$(LIBUIDIR) -l$(LIBUI)
# -L $(SDLIMGDIR) -lSDL2_image

# vpath %.c $(SRCDIR)/
# vpath %.o $(OBJDIR)/

.PHONY:  all re clean fclean $(LIBDIR)

all: $(NAME)

sdl_config:
	touch sdl_config
	cd $(PATH_SDL)/SDL2; ./autogen.sh && ./configure --prefix=$(PATH_SDL); cd $(MY_DIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(LIBDIR):
	make -C $(LIBDIR)

$(LIBUIDIR):
	mkdir -p $(LIBUIDIR)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CCFLAGS) -c -o $@ $<

$(SDL): sdl_config
	make -sC $(PATH_SDL)/SDL2
	make -sC $(PATH_SDL)/SDL2 install

#	cd $(PATH_SDL)/SDL2_image; ./configure --prefix=$(PATH_SDL) --with-sdl-prefix=$(PATH_SDL); make;
#	make -sC $(PATH_SDL)/SDL2_image install

$(NAME):  $(LIBDIR) $(SDL) $(OBJDIR) $(FULL_OBJS) sdl_config
	$(AR) $(ARFLAGS) $(LIBUIDIR)/lib$(NAME).a $(FULL_OBJS)

clean: clean_sdl
	make -C $(LIBDIR) clean
	$(RM) $(RMFLAGS) $(FULL_OBJS)

clean_sdl: sdl_config
	echo $(PATH_SDL)
	make -C $(PATH_SDL)/SDL2 clean

fclean: clean
	make -C $(LIBDIR) fclean
	$(RM) $(RMFLAGS) $(NAME)

re: fclean all

