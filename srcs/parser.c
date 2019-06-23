/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bturcott <bturcott@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 15:49:37 by bturcott          #+#    #+#             */
/*   Updated: 2019/06/04 20:10:24 by bturcott         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"


t_json *create_json_obj(void)
{
	t_json *obj;

	if (!(obj = (t_json *)malloc(sizeof(t_json))))
		return (NULL);
	if (!(obj->key = (char **)malloc(sizeof(char *) * (MAX_FIELDS + 1))))
		return (NULL);
	if (!(obj->value = malloc(sizeof(void *) * (MAX_FIELDS + 1))))
		return (NULL);
	if (!(obj->type = (int *)malloc(sizeof(int) * (MAX_FIELDS + 1))))
		return (NULL);
	obj->key[MAX_FIELDS] = NULL;
	obj->value[MAX_FIELDS] = NULL;
	return(obj);
}

int escape(t_parser *json)
{
	if (json->i > 0)
		return (json->f[json->i - 1] == '\\');
	return (0);
}

void parse_key(t_parser *json, char **key)
{
	int temp;

	temp = 0;
	while (json->f[json->i])
	{
		if (json->f[json->i] == '"')
			{
				temp = json->i;
				while (json->f[json->i])
				{
					json->i++;
					if (json->f[json->i] == '"' && !escape(json))
                    {
					    *key = ft_strsub(json->f,\
					    temp + 1, json->i - temp - 1);
					    return ;
                    }
				}
			}
		json->i++;
	}
}

int parse_int_array(t_parser *json, void **value, int len)
{
	int i;
	int *array;

	i = 0;
	if (!(array = (int *)ft_memalloc(sizeof(int) * (len + 1))))
		return (-1);
	
	while (json->f[json->i] != ']')
	{
		if (json->f[json->i] && ft_isdigit(json->f[json->i]))
		{
			array[i] = ft_atoi(json->f + json->i);
			while (json->f[json->i] && ft_isdigit(json->f[json->i]))
				json->i++;
			i++;
		}
		if (json->f[json->i] != ']')
			json->i++;
	}
	array[i] = INT_EOF;
	*value = array; //TODO types
	return (0);
}

void sanitize_string_array(char **array)
{
    int i;
    char *temp;

    i = 0;
    while (array[i])
    {
        temp = ft_strtrim(array[i]);
        free(array[i]);
        array[i] = ft_strsub(temp, 1, ft_strlen(temp) - 2);
        free(temp);
        i++;
    }
}

void parse_char_array(t_parser *json, void **value, int len)
{
    int before;
    char *temp;

    before = json->i;
    while (json->f[json->i] && json->f[json->i] != ']' && !escape(json))
        json->i++;
    //printf("%d      %d\n", json->i, before);
    //printf("%c, %c\n", json->f[json->i], json->)
    temp = ft_strsub(json->f, before + 1, json->i - before - 1);
  // printf("%d\n", json->quant);
    *value = ft_strsplit(temp, ',');
    sanitize_string_array(*value);
//    for (int i = 0; ((char**)(*value))[i]; i++)
//        printf("%s ", ((char**)(*value))[i]);
    free(temp);
	return ;
}

int parse_int(t_parser *json, void **value)
{
	int *val;
	
	if (!(val = ft_memalloc(sizeof(int))))
		return (0);
	val[0] = ft_atoi(json->f + json->i);
	while (ft_isdigit(json->f[json->i]))
		json->i++;
	*value = val;
	return (1);
}

int is_float(t_parser *json)
{
    int i;

    i = json->i;
    while (json->f[i] && json->f[i] != ',')
    {
        if (json->f[i] == '.')
            return (1);
        i++;
    }
    return (0);
}

int *scan_array(t_parser *json)
{
	int i;
	int params[2];
	
	i = json->i;
	params[0] = 1;
	params[1] = sizeof(int);
	while (json->f[json->i] && json->f[json->i] != ']')
	{
		json->i++;
		if (json->f[json->i] == '"' && (params[1] = sizeof(char)))
			while (json->f[json->i] && json->f[json->i] != '"' && !escape(json))
				json->i++;
		if (json->f[json->i] == ',')
			params[0]++;
	}
	json->i = i;
	return ((int []){params[0], params[1]});
}

void parse_float(t_parser *json, void **value)
{
    float *ret;
    float precision;

    precision = 0.1;
    ret = malloc(sizeof(float));
    *ret = 0.1;
    printf("%c\n", json->f[json->i]);
    while (json->f[json->i] && !ft_isdigit(json->f[json->i]))
        json->i++;
    printf("%c\n", json->f[json->i]);
    *ret = ft_atoi(json->f + json->i);
    printf("%f\n\n", *ret);
    while (json->f[json->i] && json->f[json->i] != '.')
        json->i++;
    while (json->f[++json->i] && ft_isdigit(json->f[json->i])) {
        *ret += (json->f[json->i] - 48) * precision;
        precision *= 0.1;
    }
    printf("%f\n\n", *ret);
    *value = ret;
}

float parse_float_to_array(t_parser *json)
{
    float value;
    float precision;

    precision = 0.1;
    value = 0.1;

    while (json->f[json->i] && !ft_isdigit(json->f[json->i]))
        json->i++;
    value = ft_atoi(json->f + json->i);
    printf("%f\n", value);
    while (json->f[json->i] && json->f[json->i] != '.')
        json->i++;
    while (json->f[++json->i] && ft_isdigit(json->f[json->i])) {
        value += (json->f[json->i] - 48) * precision;
        precision *= 0.1;
    }
    return (value);
}

void parse_float_array(t_parser *json, void **value, int len)
{
    float *array;
    int i;

    i = 0;
    array = (float *)ft_memalloc(sizeof(float) * (len + 1));

    while (json->f[json->i] && json->f[json->i] != ']')
    {
        json->i++;
        if (json->f[json->i] && ft_isdigit(json->f[json->i])) {
            array[i] = parse_float_to_array(json);
            printf("%f\n", array[i]);
            i++;
        }

    }
    array[i] = FLOAT_EOF;
    for (int m = 0; array[m] != -60000000.0; m++)
        printf("%f ", array[m]);
    *value = array;
}
/*
** params[0] - array length
** params[1] - array type(1 for char, 4 for int)
*/

int parse_array(t_parser *json, void **value, int **type)
{
	int *params;
	
	params = scan_array(json);
	if (params[1] == sizeof(int) && ((*type)[json->quant] = ARRAY_INT))
    {
	    if (is_float(json))
	        parse_float_array(json, value, params[0]);
		else
		    parse_int_array(json, value, params[0]);
    }
	else if (params[1] == sizeof(char) && ((*type)[json->quant] = ARRAY_STRING))
		parse_char_array(json, value, params[0]);
	else
		value = NULL;
	return (1);
}

int parse_value(t_parser *json, void **value, int **type)
{
	//printf("char == %c %d\n", json->f[json->i], json->i);
	while (json->f[json->i] && json->f[json->i] != '{' && !ft_isdigit(json->f[json->i]) 
	&& json->f[json->i] != '[' && json->f[json->i] != '"')
		json->i++;
	//printf("char == %c %d\n", json->f[json->i], json->i);
	if (!json->f[json->i])
		return (-1);
	else if (json->f[json->i] == '{')
	{
        printf("json!!!!!!!!!!!!!!!\n");
        ((*type)[json->quant]) = JSON;
		*value = create_json_obj();
		make_json(json, *value);
	}
	else if (json->f[json->i] == '"' && ((*type)[json->quant] = STRING))
		parse_key(json, (char **)value);
	else if (json->f[json->i] == '[')
		parse_array(json, value, type);
	else if (ft_isdigit(json->f[json->i]))
    {
	    if (is_float(json) && ((*type)[json->quant] = FLOAT))
            parse_float(json, value);
	    else if (((*type)[json->quant] = INT))
	        parse_int(json, value);
    }

	return (1);	
}

int make_json(t_parser *json, t_json *obj)
{
	int i;   
	
	json->quant = 0;
	while (json->f[json->i] && json->f[json->i] != '}')
	{
		if (json->quant > MAX_FIELDS)
			return(-1);
		parse_key(json, &obj->key[json->quant]);
		// printf("%d\n", json->i);

		while (json->f[json->i] && json->f[json->i] != ':')
			json->i++;
		if (parse_value(json, &obj->value[json->quant], &obj->type) == -1)
			return (1);
        printf("key == %s  ", obj->key[json->quant]);
		printf("value == %d\n", ((int *)(obj->value[json->quant]))[0]);
		if (json->f[json->i] && json->f[json->i] != '}')
			json->i++;
		//printf("make\n");
		json->quant++;
	}
	obj->type[json->quant] = 0;
	obj->value[json->quant] = NULL;
	obj->key[json->quant] = NULL;
	return (1);
}

t_list *json_operator(t_parser *json)
{
	int ind;
	t_json *obj;
	
	while (json->f[json->i])
	{
		if (json->f[json->i] == '{')
		{
			json->i++;
			if (!(obj = create_json_obj()))
				return (NULL);
			//printf("json!!!!\n");
			make_json(json, obj);
			t_json *json1 =((t_json *)obj->value[2]);
            //printf("%p\n", json1->value);
           // printf("%d\n", ((int* )json1->value[1])[0]);
//			for (int i = 0; obj->type[i]; i++)
//				if (obj->type[i] == ARRAY_INT)
//				{
//
//						printf("type == %d  key == %s ", obj->type[i], obj->key[i]);
//						printf("inarr:  ");
//					for(int j = 0; ((int*)obj->value[i])[j] != -2147483648; j++)
//						printf("%d ", ((int *)obj->value[i])[j]);
//						printf("\n");
//				}
//			    else if (obj->type[i] == ARRAY_STRING)
//                    for (int k = 0; ((char**)(obj->value[i]))[k]; k++)
//                        printf("%s ", ((char**)(obj->value[i]))[k]);
//				else
//					printf("type == %d  key == %s  value == %d\n", obj->type[i], obj->key[i], ((int *)obj->value[i])[0]);
			ft_lstadd(&json->objects, ft_lstnew((void *)obj, sizeof(t_json)));
			printf("+list\n");
		}
		
		json->i++;
	}

	return NULL;
}

char *read_file(int fd){
	
	char *file;
	char *temp;
	char *temp2;
	int i;
	
	i = 0;
	temp2 = ft_strdup("\0");
	while (get_next_line(fd, &temp))
	{
		file = ft_strjoin(temp2, temp);
		free(temp2);
		free(temp);
		temp2 = file;
	}
	return (file);
}

t_list *parse_json(char *config_file)
{
	int fd;
	t_parser *json;
	
	fd = open(config_file, O_RDONLY);
	if (fd == -1 || fd == 0)
	{   
		ft_putendl("Missing json file...");
		exit(0);
	}
	if (!(json = ft_memalloc(sizeof(t_parser))))
		return (NULL);
	if (!(json->f = read_file(fd)))
		return (NULL);
	json->i = 0;
	json->objects = NULL;
	close(fd);
	json_operator(json);
	return(NULL);
}


int main(int ac, char **av)
{
	t_list *json = parse_json(av[1]);
	// convert_objects(json);
}