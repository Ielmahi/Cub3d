#include "cub3d.h"
#define INVALID_ARGS "\033[0;31mError\nInvalid Arguments\n\033[0m"
#define INVALID_FILE "\033[0;31mError\nInvalid File\n\033[0m"
#define OPEN_FILE_ERROR "\033[0;31mError\nCannot Open FILE\n\033[0m"
#define POINT '.'

#define EXTENSION ".cub"
#define SLASH '/'
#define TRUE 1
#define FALSE 0
#include <fcntl.h>

typedef struct s_color
{
    int floor_color[3];
    int cell_color[3];
}t_color;
typedef struct s_map
{
    char **map2D;
    int fd;
    int read_bytes;
    t_color colors; 
} t_map;
void ft_error_msg(char *msg)
{
    write(STDERR_FILENO, msg, ft_strlen(msg));
    exit(TRUE);
}

void  read_info(t_map *map)
{
      char *line;
      int i = 0;
      while(1)
      {
          line = get_next_line(map->fd);
          if(!line)
              break;
          map->map2D[i++] = ft_strdup(line);
      }
      map->map2D[i] = NULL;
      i = -1;
      while(map->map2D[++i])
            printf("%s", map->map2D[i]);
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
      if(str && (str[0] == POINT || !name ))//|| ft_strlen(name) != 4))
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
    
    ft_memset(&parse, 0, sizeof(parse));
    if(ac != 2)
        ft_error_msg(INVALID_ARGS);
    check_and_read_error(&parse, av[1]);

}
