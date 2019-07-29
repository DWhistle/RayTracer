/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftui.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/09 17:22:10 by hgreenfe          #+#    #+#             */
/*   Updated: 2019/07/29 21:52:57 by hgreenfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTUI_H
# define FTUI_H

# define FTUI_MOUSE_LEFT 1
# define FTUI_MOUSE_RIGHT 3
# define FTUI_MOUSE_MIDDLE 2
# define FTUI_KEY_ESCAPE 41

typedef	struct	s_rect {
	int			x;
	int			y;
	int			w;
	int			h;
}				t_rect;

typedef struct	s_point {
	int			x;
	int			y;
}				t_point;

typedef enum			e_event_type {
	FT_EVENT_DEFAULT,
	FT_EVENT_RENDER,
	FT_EVENT_BEFORECLOSE,
	FT_EVENT_WINDOWFUNC,
	FT_EVENT_TICKFUNC,
	FT_EVENT_MOUSEMOVE,
	FT_EVENT_MOUSEUP,
	FT_EVENT_MOUSEDOWN,
	FT_EVENT_KEYPRESS
}						t_event_type;

typedef	void	(*t_controlevent_func)(void *const, int, void *const);
typedef void	(*t_windowevent_func)(void *const, int, void *const);

/*
**libui common functions
*/
unsigned int	ft_correct_quit(void *libui);
void			ft_mainloop(void *libui);
void			*ft_libui_init(void);
t_rect			ft_new_rect(int x, int y, int w, int h);
void			draw_line(void *wnd, t_point *start_end, int color, int size);
void			ft_draw_rect(int *pxls, t_rect *rect, int width, int color);

/*
**libui control functions
*/
void			*ft_create_new_control(t_rect r, unsigned int color);
void			ft_clear_control(void *ctrl);
void			ft_delete_control(void **cntrl);
int				ft_attach_to_window(void *ctrl, void *wnd);
int				ft_attach_to_control(void *ctrl, void *p);
int				ft_dettach_from_window(void *ctrl, void *wnd);
int				ft_dettach_from_control(void *find, void *p);
t_rect			ft_get_control_rect(void *ctrl);
unsigned int	ft_get_control_color(void *ctrl);
void			*ft_get_control_param(void *ctrl);
void			*ft_get_control_parent(void *ctrl);
void			ft_set_control_rect(void *ctrl, t_rect rect);
void			ft_set_control_color(void *ctrl, unsigned int bg_color);
void			ft_set_control_param(void *ctrl, void *param);

/*
** libui window functions
*/
void			*ft_create_new_window(void);
void			ft_set_window_position(void *wnd, int x, int y);
void			ft_set_window_size(void *wnd, int w, int h);
void			ft_set_window_color(void *wnd, unsigned int color);
void			ft_set_window_title(void *wnd, char const *title);
void			ft_set_window_quit(void *wnd, int quit);
void			ft_set_window_pixels(void *wnd, int *pxls, t_rect *rect);
t_point			ft_get_window_position(void *wnd);
t_point			ft_get_window_size(void *wnd);
unsigned int	ft_get_window_color(void *wnd);
char const		*ft_get_window_title(void *wnd);
int				ft_get_window_quit(void *wnd);
int				*ft_get_window_pixels(void *wnd, t_rect *rect);
void			ft_close_window(void **wnd);
int				ft_show_window(void *wnd);
int				add_window(void **libui, t_rect rect,
					int color, char const *title);
void			*ft_get_window_input_param(void *wnd);
void			*ft_get_window_render_param(void *wnd);
void			*ft_get_window_window_param(void *wnd);
void			ft_set_window_input_param(void *wnd, void *param);
void			ft_set_window_render_param(void *wnd, void *param);
void			ft_set_window_window_param(void *wnd, void *param);

/*
** libui event functions
*/
int				set_event_function(void *wnd, t_event_type eventtype,
					t_windowevent_func func, void *param);
int				set_controlevent_function(void *ctrl, t_event_type eventtype,
					t_controlevent_func func, void *param);
void			ft_window_redraw(void *wnd, int num, void *param);
void			ft_window_process(void *wnd, int num, void *param);

/*
** mouse and keys events
*/
t_point			ft_get_mousepos(void);
t_point			ft_get_mouse_event_state(void *event, int *state);
char			ft_is_key_pressed(void *wnd, int keycode);
int				ft_get_mouseevent(void *event_param);
#endif
