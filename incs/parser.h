/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 16:14:59 by bturcott          #+#    #+#             */
/*   Updated: 2019/06/04 21:03:44 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "libft.h"
#include <fcntl.h>
#include "get_next_line.h"
#define MAX_FIELDS 10

#define INT 6
#define ARRAY_INT 2
#define ARRAY_STRING 4
#define STRING 1
#define JSON 3
#define FLOAT_EOF -60000000.0
#define INT_EOF -2147483648
#define FLOAT 7

typedef struct s_json_object{
   char **key;
   void **value;
   int *type;
}              t_json;

typedef struct s_json_parser{
   int quant;
   t_list *objects;
   int i;
   char *f;
}              t_parser;

int convert_objects(t_list *objs);
int make_json(t_parser *json, t_json *obj);

enum
{
    OBJ = 0,
    CYLINDER = 1,
    SPHERE = 2,
    CONE = 3,
    PLANE = 4,
    LIGHT = 5,
    SCENE = 6,
    POINT_DATA = 7,
    ACCURACY = 8
};

#endif
