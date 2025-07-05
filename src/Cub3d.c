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
    char *extension;
    char *slash;

    slash = ft_strrchr(str, SLASH);
    extension = ft_strnstr(str, EXTENSION, ft_strlen(str));
    if(str && (str[0] == DOT || !extension || ft_strlen(extension) != 4))
        return(FALSE);
    else if (slash &&  *(slash + 1) == DOT)
            return (FALSE);
    return (TRUE);
}

void check_and_read_error(t_map *parse, char *str)
{
    (void)parse;
    if(!check_file(str))
        ft_error_msg(INVALID_FILE);
    open_and_read_file(str, parse);
}

char    *skip_char(char *str, char skip)
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
        ft_error_msg(ERR_INVALID_PATH);
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
        ft_error_msg(ERR_OUT_OF_RANGE);
    else if (map->c_color.r<0 || map->c_color.r>255 || map->c_color.g<0||map->c_color.r>255|| map->c_color.b<0 || map->c_color.b>255)
        ft_error_msg(ERR_OUT_OF_RANGE);
}

int parse_color(char ***path_start, char **comma_pos, size_t *len, int is_last)
{
    char *rgb_str;
    
    *comma_pos = ft_strchr(**path_start, ',');
    if (*comma_pos == NULL)
    {
        *len = ft_strlen(**path_start);
        rgb_str = ft_strndup(**path_start, *len);
        **path_start = **path_start + *len;
    }
    else
    {
        *len = *comma_pos - **path_start;
        rgb_str = ft_strndup(**path_start, *len);
        if (is_last)
        {
            **path_start = **path_start + *len;
            if (***path_start != '\0')
                ft_error_msg(ERR_EXTRA_CHAR);
        }
        else
            **path_start = skip_char(**path_start + *len, ',');
    }
    return (ft_atoi(rgb_str));
}


void    parse_ceiling_color(t_map *map, char **path_start, int i)
{
    char *comma_pos;
    size_t len;

    if (map->c_color.is_set_c >= 1)
        ft_error_msg(ERR_DUP_CEILING);
    *path_start = skip_char(map->map2D[i]+1, ' ');
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

    if (map->f_color.is_set_f >= 1)
        ft_error_msg(ERR_DUP_FLOOR);
    *path_start = skip_char(map->map2D[i]+1, ' ');
    map->f_color.r = parse_color(&path_start, &comma_pos, &len, 0);
    map->f_color.g = parse_color(&path_start, &comma_pos, &len, 0);
    map->f_color.b = parse_color(&path_start, &comma_pos, &len, 1);
    check_colors(map);
    map->f_color.is_set_f += 1;
}

void    is_path_valid(char *str)
{
    char **path;

    path = ft_split(str, ' ');
    if (lengh_of_2d_array(path) > 1)
        ft_error_msg(ERR_INVALID_PATH);
}


void    we(t_map *map, char *path_start)
{
    is_path_valid(path_start);
    if (map->texture->west == NULL)
        map->texture->west = ft_strdup(path_start);
    else
        ft_error_msg(ERR_DUP_WEST);
}

void    ea(t_map *map, char *path_start)
{
    is_path_valid(path_start);
    if (map->texture->east == NULL)
        map->texture->east = ft_strdup(path_start);
    else
        ft_error_msg(ERR_DUP_EAST);
}

void    so(t_map *map, char *path_start)
{
    is_path_valid(path_start);
    if (map->texture->south == NULL)
        map->texture->south = ft_strdup(path_start);
    else
        ft_error_msg(ERR_DUP_SOUTH);
}

void    no(t_map *map, char *path_start)
{
    is_path_valid(path_start);
    if (map->texture->north == NULL)
        map->texture->north = ft_strdup(path_start);
    else
        ft_error_msg(ERR_DUP_NORTH);
}

bool    check_textures_and_colors(t_map *map, int i, char *path_start)
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
    while(map->map2D[++i])
    {
        check_erros(map->map2D[i]);
        path_start = skip_char(map->map2D[i]+2, SPACE);
            if(!*path_start) ft_error_msg(ERR_EMPTY_PATH);
        if (!check_textures_and_colors(map, i, path_start))
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
    texture->map = malloc((ft_errlen(map)+1)* sizeof(char*));
    int i = 0;
    size_t len = 0, j = 0;
    while(map[i])
    {
     
        if(max_lenght > ft_strlen(map[i]))
          len = ft_strlen(map[i]) + (max_lenght - ft_strlen(map[i]));
        else len = ft_strlen(map[i]);
       texture->map[i] = malloc(sizeof(char) * (len +1));
        j = 0;
        while(j < len)
        {
            if(j < ft_strlen(map[i]))
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
        return(0);
    max_lenght = get_max_line_length(map);
    pad_line_with_spaces(texture, max_lenght, map);
  return 1;
}
int is_check(char c)
{
    return (c == ' ' || c == 'N' || c == '1' || c == '0' || c  == 'S' || c=='W' || c == 'E');
}
int is_player(char c)
{
  return (c =='E' || c == 'N' || c == 'W' || c == 'S');
}
int validate_charactere_and_palyer(char **map)
{
    int i =0, j;
    int player =0;
    while(map[i])
    {
        j = 0;
        while(map[i][j])
        {
          if(!is_check(map[i][j]))
              return(FALSE);
          if(is_player(map[i][j]))
              player++;
        j++;
        }
    i++;
    }
    if(player != 1) return(FALSE);
  return(TRUE);
}
int is_check_lines(char *ptr)
{
  while(*ptr && (*ptr == SPACE || *ptr == WALL))
        ptr++;
  return(*ptr);
}
int validate_border_lines(char **map)
{
    int i = 0;
    while(map[i])
    {
        if(i == 0 || i == (ft_errlen(map) - 1))
            if(is_check_lines(map[i]))
                return(FALSE);
      i++;
    }
  return(TRUE);
}
int validate_border_columns(char **map)
{
    int i = 0, j = ft_strlen(map[i]) - 1;
  while(map[i])
  {
    if((map[i][0] != SPACE && map[i][0] != WALL) || (map[i][j] != SPACE && map[i][j] != WALL))
                return FALSE;
    i++;
  }
  return TRUE;
}
void get_coordinate(char **map, t_texture *texture)
{
    int i = 0, j;
    while(map[i])
    {
        j = 0;
      while (map[i][j]) 
      {
        if(is_player(map[i][j]))
        {
          texture->x_player = j;
          texture->y_player = i;
          texture->position_player = map[i][j];
        }
        j++;
      }
    i++;
    }
}
int flood_fill(char **map, int x, int y, t_texture *texture)
{
    if (x < 0 || y < 0 || !map[y] || !map[y][x])
        return FALSE;
    if (map[y][x] == '1' || map[y][x] == 'x')
        return TRUE;

    if (map[y][x] == ' ')
        return FALSE;

    map[y][x] = 'x';

    int valid = flood_fill(map, x - 1, y, texture) &&
                flood_fill(map, x + 1, y, texture) &&
                flood_fill(map, x, y - 1, texture) &&
                flood_fill(map, x, y + 1, texture);
    return valid;
}
int check_last_zero(char **map)
{
    int i = 0;
    int j;

    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            char c = map[i][j];
            if (c == EMPTY)
            {
               if (!map[i + 1] || i == 0 || !map[i - 1])
                    return FALSE;
                if (j == 0 || map[i][j + 1] == '\0')
                    return FALSE;
                if (map[i + 1][j] != EMPTY && map[i + 1][j] != WALL)
                    return FALSE;
                if (map[i - 1][j] != EMPTY && map[i - 1][j] != WALL)
                    return FALSE;
                if (map[i][j + 1] != EMPTY && map[i][j + 1] != WALL)
                    return FALSE;
                if (map[i][j - 1] != EMPTY && map[i][j - 1] != WALL)
                    return FALSE;
            }
            j++;
        }
        i++;
    }
    return TRUE;
}
void  check_validite_map(t_map *map)
{
      char **map_start = map->map2D + map->texture->start;
      get_coordinate(map_start, map->texture);
      int x = map->texture->x_player;
      int y = map->texture->y_player;
    if(!normalize_map(map->texture, map_start))
        ft_error_msg("error here a\n");             
     else if(!validate_charactere_and_palyer(map->texture->map))
        ft_error_msg("Error here b\n");
    else if(!validate_border_lines(map->texture->map))
          ft_error_msg("error here c\n");
    else if (!validate_border_columns(map->texture->map))
          ft_error_msg("error here d\n");
     if(!flood_fill(map->texture->map , x, y, map->texture))
          ft_error_msg("Error here boxee\n");
    if(!check_last_zero(map->texture->map))
          ft_error_msg("Error here wal ilias\n");
      
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
    //TODO: Starting Rycasting Tomorrow 
}
