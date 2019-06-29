/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmeera-r <kmeera-r@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/24 17:31:11 by bturcott          #+#    #+#             */
/*   Updated: 2019/06/29 19:13:38 by kmeera-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "objects.h"
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

t_vec *get_vec(void *value){
    t_vec *vec;
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

t_obj *get_obj(t_json *obj, char *name)
{
    t_json *json;
    t_obj *object;
    json = (t_json*)query_attribute(obj, name);
    object = (t_obj*)ft_memalloc(sizeof(t_obj));
    object->reflection = *((double*)query_attribute(obj, "reflection"));
    object->refraction = *((double*)query_attribute(obj, "refraction"));
}