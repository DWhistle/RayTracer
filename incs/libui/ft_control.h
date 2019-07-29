/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_control.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hgreenfe <hgreenfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 19:08:41 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_CONTROL_H
# define FT_CONTROL_H

# include "ftui.h"
# include "SDL2/SDL.h"
# include "libft.h"
# include "libui/ft_window.h"

struct s_control;
typedef enum			e_state {
	S_NONE,
	S_FOCUSED,
	S_PRESSED,
	S_DISABLED
}						t_state;

/*
** t_control
** состоит из прямоугольника(rect) описывающего положение
** внтури родительского окна(parent)
** состяния(state) определяющего есть ли на элементе фокус,
** нажата ли на нём какая-либо кнопка или активен ли элемент
** список дочерних элементов(children)
** события элемента
*/
typedef struct			s_control {
	t_rect				rect;
	void				*pixels;
	SDL_Texture			*texture;
	SDL_Surface			*surface;
	t_window			*parent;
	int					state;
	unsigned int		bg_color;
	void				*param;
	t_list				*children;
	t_controlevent_func	onmousemove;
	t_controlevent_func	onmousedown;
	t_controlevent_func	onmouseup;
	t_controlevent_func	ondraw;
	t_controlevent_func	ontickfunc;
}						t_control;

void					ft_redraw(t_list *lst);

#endif
