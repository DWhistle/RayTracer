/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:14:59 by bturcott          #+#    #+#             */
/*   Updated: 2019/07/17 11:11:56 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "libft.h"
#include <fcntl.h>
#include "get_next_line.h"
#define MAX_FIELDS 30

#define INT 6
#define ARRAY_INT 2
#define ARRAY_STRING 4
#define STRING 1
#define JSON 3
#define FLOAT_EOF -60000000.0
#define INT_EOF -2147483648
#define FLOAT 7

typedef struct s_json t_json;

typedef union u_value{
   int int_value;
   char *string_value;
   int *intarr_value;
   double float_value;
   t_json *json_value;
}             t_values;


#define INT 6
#define ARRAY_INT 2
#define ARRAY_STRING 4
#define STRING 1
#define JSON 3
#define FLOAT_EOF -60000000.0
#define INT_EOF -2147483648
#define FLOAT 7

typedef struct s_json{
   char **key;
   t_values *value;
   int *type;
}              t_json;

typedef struct s_json_parser{
   int quant;
   t_list *objects;
   int i;
   char *f;
}              t_parser;


void *convert_objects(t_json *j);
int make_json(t_parser *json, t_json *obj);
t_list *parse_json(char *config_file);
char	**gate_names_obj(t_json *j);

#endif
