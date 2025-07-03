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

char    *SkipChar(char *str, char skip)
{
    while(*str)
    {
        if (*str == skip)
            str++;
        else
            break;
    }
    return str;
}

void    check_erros(char *str)
{
    if (ft_strlen(str) < 3)
        ft_error_msg("invalid path to textures\n");
}

int     lengh_of_2d_array(char **arr)
{
    int i = 0;
    while(arr[i])
        i++;
    return i;
}


void    check_colors(t_map *map)
{
    if (map->f_color.r<0 || map->f_color.r>255 || map->f_color.g<0||map->f_color.r>255|| map->f_color.b<0 || map->f_color.b>255)
        ft_error_msg("Error: RGB color values out of range [0-255]\n");
    else if (map->c_color.r<0 || map->c_color.r>255 || map->c_color.g<0||map->c_color.r>255|| map->c_color.b<0 || map->c_color.b>255)
        ft_error_msg("Error: RGB color values out of range [0-255]\n");
}


int parse_color(char ***path_start, char **comma_pos, size_t *len, int is_last)
{
    char *r_str;
    
    *comma_pos = ft_strchr(**path_start, ',');
    if (*comma_pos == NULL)
    {
        *len = ft_strlen(**path_start);
        r_str = ft_strndup(**path_start, *len);
        **path_start = **path_start + *len;
    }
    else
    {
        *len = *comma_pos - **path_start;
        r_str = ft_strndup(**path_start, *len);
        if (is_last)
        {
            **path_start = **path_start + *len;
            if (***path_start != '\0')
                ft_error_msg("Error: Extra characters after color definition\n");
        }
        else
            **path_start = SkipChar(**path_start + *len, ',');
    }
    return (ft_atoi(r_str));
}


void    parse_ceiling_color(t_map *map, char **path_start, int i)
{
    char *comma_pos;
    size_t len;

    if (map->c_color.is_set_c > 2)
        ft_error_msg("Error: Duplicate Ceilling color\n");
    *path_start = SkipChar(map->map2D[i]+1, ' ');
    map->c_color.r = parse_color(&path_start, &comma_pos, &len, 0);
    map->c_color.g = parse_color(&path_start, &comma_pos, &len, 0);
    map->c_color.b = parse_color(&path_start, &comma_pos, &len, 1);
    check_colors(map);
    map->c_color.is_set_c += 1;
}

void    parse_floor_color(t_map *map, char **path_start, int i)
{
    char *comma_pos;
    size_t len;

    if (map->c_color.is_set_f > 2)
        ft_error_msg("Error: Duplicate Floor color\n");
    *path_start = SkipChar(map->map2D[i]+1, ' ');
    map->f_color.r = parse_color(&path_start, &comma_pos, &len, 0);
    map->f_color.g = parse_color(&path_start, &comma_pos, &len, 0);
    map->f_color.b = parse_color(&path_start, &comma_pos, &len, 1);
    check_colors(map);
    map->f_color.is_set_c += 1;
}

void    we(t_map *map, char *path_start)
{
    if (map->texture->west == NULL)
            map->texture->west = ft_strdup(path_start);
        else
            ft_error_msg("Error: Duplicate West texture path\n");
}

void    ea(t_map *map, char *path_start)
{
    if (map->texture->east == NULL)
        map->texture->east = ft_strdup(path_start);
    else
        ft_error_msg("Error: Duplicate East texture path\n");
}

void    so(t_map *map, char *path_start)
{
    if (map->texture->south == NULL)
            map->texture->south = ft_strdup(path_start);
    else
        ft_error_msg("Error: Duplicate South texture path\n");
}

void    no(t_map *map, char *path_start)
{
    if (map->texture->north == NULL)
        map->texture->north = ft_strdup(path_start);
    else
        ft_error_msg("Error: Duplicate North texture path\n");
}

bool    check(t_map *map, int i, char *path_start)
{
    if (!ft_strncmp(map->map2D[i], "NO ", 3))
        no(map, path_start);
    else if (!ft_strncmp(map->map2D[i], "SO ", 3))
        so(map, path_start);
    else if (!ft_strncmp(map->map2D[i], "WE ", 3))
        we(map, path_start);
    else if (!ft_strncmp(map->map2D[i], "EA ", 3))
        ea(map,path_start);
    else if (!ft_strncmp(map->map2D[i], "F ", 2))
        parse_floor_color(map, &path_start, i);
    else if (!ft_strncmp(map->map2D[i], "C ", 2))
        parse_ceiling_color(map, &path_start, i);
    else
        return false;
    return true;
}


void    parse_textures(t_map *map)
{
    int i = -1;
    char *path_start;
    map->texture = malloc(sizeof(t_texture));
    ft_memset(map->texture, 0, sizeof(t_texture));

    //char **colors;
    while(map->map2D[++i])
    {
        check_erros(map->map2D[i]);
        path_start = SkipChar(map->map2D[i]+2, SPACE);
            if(!*path_start) ft_error_msg("Error: Empty path for texture\n");
        if (!check(map, i, path_start))
            break;
        map->texture->start++;
    }
    if(map->texture->start != 6) printf("invalid content"), exit(1);
}

int get_max_line_length(char **map)
{
    int i = 0;
   size_t max = ft_strlen(map[i]);
    
    while(map[i])
    {
      if(ft_strlen(map[i]) > max)
          max = ft_strlen(map[i]);
      i++;
    }
    return max;
}
int ft_errlen(char **map)
{
  int i = 0;
    while(map[i])
            i++;
  return i;
}
void pad_line_with_spaces(t_texture *texture, size_t max_lenght, char **map)
{
    texture->map = malloc(ft_errlen(map) * sizeof(char*));
    int i = 0;
    size_t len = 0, j = 0;
    while(map[i])
    {
      j = 0;
        if(max_lenght > ft_strlen(map[i]))
          len = ft_strlen(map[i]) + (max_lenght - ft_strlen(map[i]));
        else len = ft_strlen(map[i]);
       texture->map[i] = malloc(sizeof(char) * len);
        while(j < len)
        {
            if(map[i][j])
                texture->map[i][j] = map[i][j];
            else
                texture->map[i][j] = ' ';
          j++;
        }
        texture->map[i][j] = '\0';
        i++;
    }
        texture->map[i] = NULL;
}
int normalize_map(t_texture *texture, char **map)
{
    size_t max_lenght;

    if(!*map) 
        ft_error_msg("Here error msg\n");
    max_lenght = get_max_line_length(map);
    pad_line_with_spaces(texture, max_lenght, map);
  return 1;
}
void  check_validite_map(t_map *map)
{
    
    if(!normalize_map(map->texture, map->map2D+=map->texture->start))
        ft_error_msg("error here\n");
}
int main(int ac, char **av)
{
    t_map parse;
    
    parse = (t_map){0};
    if(ac != 2)
        ft_error_msg(INVALID_ARGS);
    check_and_read_error(&parse, av[1]);
    parse_textures(&parse);
    check_validite_map(&parse);
}
