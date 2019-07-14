
#include "parser.h"


t_json *create_json_obj(void)
{
	t_json *obj;

	if (!(obj = (t_json *)malloc(sizeof(t_json))))
		return (NULL);
	if (!(obj->key = (char **)malloc(sizeof(char *) * (MAX_FIELDS + 1))))
		return (NULL);
	if (!(obj->value = malloc(sizeof(t_values) * (MAX_FIELDS + 1))))
		return (NULL);
	if (!(obj->type = (int *)malloc(sizeof(int) * (MAX_FIELDS + 1))))
		return (NULL);
	obj->key[MAX_FIELDS] = NULL;
	return(obj);
}

int escape(t_parser *json)
{
	if (json->i > 0)
		return (json->f[json->i - 1] == '\\');
	return (0);
}


void print_values(t_values val, int type){
	if (type == FLOAT)
		printf("%f   is a value\n", val.float_value);
	else if (type == INT)
		printf("%d   is a value\n", val.int_value);
	else if (type == STRING)
		printf("%s   is a value\n", val.string_value);
	else if (type == JSON)
		printf("JSON %p\n", &val);
	printf("================\n");
}
int parse_key(t_parser *json, char **key)
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
						//printf("%s\n", *key);
					    return (1);
                    }
				}
			}
		json->i++;
	}
	return (0);
}

int parse_float(t_parser *json, t_values *value)
{
    double ret;
    double precision;

    precision = 0.1;
    ret = 0.0;
    //printf("%c\n", json->f[json->i]);
    while (json->f[json->i] && !ft_isdigit(json->f[json->i]) && json->f[json->i] != '-')
        json->i++;
    //printf("%c\n", json->f[json->i]);
    ret = ft_atoi(json->f + json->i);
	precision = (ret > 0) ? precision : -precision;
    //printf("%f\n\n", *ret);
    while (json->f[json->i] && json->f[json->i] != '.')
        json->i++;
    while (json->f[++json->i] && ft_isdigit(json->f[json->i])) {
        ret += (json->f[json->i] - 48) * precision;
        precision *= 0.1;
    }
    //printf("%f\n\n", ret);
    (*value).float_value = ret;
	return (1);
}

int parse_int(t_parser *json, t_values *value)
{
	int *val;
	
	// if (!(val = ft_memalloc(sizeof(int))))
	// 	return (0);
	// val[0] = ft_atoi(json->f + json->i);
	// while (ft_isdigit(json->f[json->i]))
	// 	json->i++;
	(*value).int_value = ft_atoi(json->f + json->i);
	//rintf("%d\n", (*value).int_value);
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



int parse_value(t_parser *json, t_values *value, int **type, int i)
{
	while (json->f[json->i])
    {
        if (json->f[json->i] == '{')
        {
            ((*type)[i]) = JSON;
            value[i].json_value = create_json_obj();
           // printf("MAKE JSOOOOOOOOON\n");
            return(make_json(json, value[i].json_value));
        }
        else if (json->f[json->i] == '"' && ((*type)[i] = STRING))
            return (parse_key(json, &(value[i].string_value)));
        // else if (json->f[json->i] == '[')
        //     parse_array(json, value, type);
         else if (ft_isdigit(json->f[json->i]) || json->f[json->i] == '-')
         {
            if (is_float(json) && ((*type)[i] = FLOAT))
                return (parse_float(json, &(value[i])));
            else if (((*type)[i] = INT))
                return (parse_int(json, &(value[i])));
        }
        json->i++;
    }
	return (1);	
}



int make_json(t_parser *json, t_json *obj)
{
	int i;   
	
	i = 0;
	while (json->f[json->i] && json->f[json->i] != '}')
	{
		if (i > MAX_FIELDS)
			return(-1);
		parse_key(json, &obj->key[i]);
        printf("%s   is a key\n", obj->key[i]);
		while (json->f[json->i] && json->f[json->i] != ':')
			json->i++;
		if (parse_value(json, obj->value, &obj->type, i) == -1)
			return (1);
			//printf("%p\n", obj->value[i]);
		print_values(obj->value[i], obj->type[i]);
        
        //printf("%c\n", json->f[json->i]);
		while (json->f[json->i] && json->f[json->i] != ',' && json->f[json->i] != '}')
			json->i++;
		//printf("\nsymbol at %d %c\n", json->i,json->f[json->i]);
		i++;
	}
	// printf("\ncycle left\n");
	 json->i += (json->f[json->i]) ? 1 : 0;
	// printf("%s\n\n", json->f + json->i);
	// printf("%d\n\n", json->i);
	obj->type[i] = 0;
	obj->key[i] = NULL;
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
		    make_json(json, obj);
			//printf("%d\n", obj->value[5].json_value->value[0].json_value->value[1].int_value);
		    ft_lstadd(&json->objects, ft_lstnew((void *)obj, sizeof(t_json)));
            //printf("%p\n", obj->value[0].json_value->value[0]);
			//printf("+list\n");
		
		}
		json->i += (json->f[json->i]) ? 1 : 0;
	}
	return json->objects;
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
	return json_operator(json);
}


int main(int ac, char **av)
{
	t_list *json1 = parse_json(av[1]);
	convert_objects(json1->content);
}