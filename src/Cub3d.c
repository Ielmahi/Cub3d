#include "../includes/cub3d.h"

void ft_error_msg(char *msg)
{
    write(STDERR_FILENO, msg, ft_strlen(msg));
    exit(TRUE);
}

void  read_info(t_map *map)
{
    char *line = get_next_line(map->fd);
      
    char *content = NULL, *tmp;
    while(line)
    {
        tmp = content;
        content = ft_strjoin(content, line);
        free(line), free(tmp);
        line = get_next_line(map->fd);
        if(!line)
            break;
    }
    map->map2D = ft_split(content, NEW_LINE);
    if(!map->map2D)
        ft_error_msg(INVALID_MAP);
    // int i = -1;
    // while(map->map2D[++i]) printf("%s\n", map->map2D[i]);
}

void open_and_read_file(char *str, t_map *map)
{
    map->fd = open(str, O_RDONLY);
    if(map->fd == -1)
        ft_error_msg(OPEN_FILE_ERROR);
    read_info(map);
}

int check_file(char *str)
{
    char *name;
    name = ft_strnstr(str, EXTENSION, ft_strlen(str));
    
    if(str && (str[0] == POINT || !name || ft_strlen(name) != 4))
        return(FALSE);
    else if(ft_strchr(str, SLASH) && (name && name[0] == POINT))
        return(FALSE);
    return (TRUE);
}

void check_and_read_error(t_map *parse, char *str)
{
    (void)parse;
    if(!check_file(str))
        ft_error_msg(INVALID_FILE);
    open_and_read_file(str, parse);
}




int main(int ac, char **av)
{
    t_map parse;
    
    parse = (t_map){0};
    if(ac != 2)
        ft_error_msg(INVALID_ARGS);
    check_and_read_error(&parse, av[1]);
    parse_textures(&parse);
}
