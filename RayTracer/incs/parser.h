/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:14:59 by bturcott          #+#    #+#             */
/*   Updated: 2019/10/13 20:21:23 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# define MAX_FIELDS 30
# define INT 6
# define STRING 1
# define JSON 3
# define FLOAT 7
# include "libft.h"
# include <fcntl.h>
# include "get_next_line.h"

typedef union			u_value {
	int					int_value;
	char				*string_value;
	double				float_value;
	struct s_json		*json_value;
}						t_values;

typedef struct			s_json {
	char				**key;
	t_values			*value;
	int					*type;
}						t_json;

typedef struct			s_json_parser {
	t_list				*objects;
	int					i;
	char				*f;
}						t_parser;

void					*convert_objects(t_json *j);
int						make_json(t_parser *json, t_json *obj);
t_list					*parse_json(char *config_file);
int						gate_names_obj(t_json *j, char ***names,
							int (*check_names)());
int						parse_value(t_parser *json, t_values *value,
							int **type, int i);
t_json					*create_json_obj(void);

/*
** logic
*/
int						parse_key(t_parser *json, char **key);
int						parse_int(t_parser *json, t_values *value);
int						parse_float(t_parser *json, t_values *value);

/*
** utils
*/
int						is_float(t_parser *json);
int						escape(t_parser *json);
void					free_json_obj(t_json *obj);

#endif
