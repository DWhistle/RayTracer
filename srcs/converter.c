/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:31:11 by bturcott          #+#    #+#             */
/*   Updated: 2019/06/27 19:26:03 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"



int get_int(void *value)
{
    return ((int *)value)[0];
}

float get_float(void *value)
{
    return (((float *)value)[0]);
}

float *get_float_array(void *value){
    return ((float *)value);
}

int *get_int_array(void *value){
    return ((int *)value);
}

char *get_string(void *value){
    return ((char*)value);
}

char **get_string_array(void *value){
    return ((char **)value);
}


void *query_attribute(t_json *obj, char *name)
{
    int i;

    i = 0;

    while (obj->type[i] != 0)
    {
        if (!ft_strcmp(obj->key[i], name))
            return obj->value[i];
        i++;
    }
    return NULL;
}

int convert_objects(t_list *objs)
{  
    t_json *obj;
    int i;

    
    i = -1;
    obj = (t_json *)objs->content;
    float *m = get_float_array(query_attribute(obj, "key2"));
    printf("%f\n", m[0]);
    return (m);
}
