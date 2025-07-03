#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Libft/libft.h"
#include <fcntl.h>


#define INVALID_ARGS "\033[0;31mError\nInvalid Arguments\n\033[0m"
#define INVALID_FILE "\033[0;31mError\nInvalid File\n\033[0m"
#define OPEN_FILE_ERROR "\033[0;31mError\nCannot Open FILE\n\033[0m"
#define POINT '.'
#define NEW_LINE '\n'
#define INVALID_MAP "\033[0;31mError\nInvalid Map\n\033[0m"
#define EXTENSION ".cub"
#define SLASH '/'
#define TRUE 1
#define FALSE 0
#define SPACE ' '
#define COMMA ','


typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_texture
{
    char *north;
    char *south;
    char *west;
    char *east;
    char **map;
    int start;
}   t_texture;

typedef struct s_map
{
    char **map2D;
    int fd;
    int read_bytes;
    t_color floor_color;
    t_color ceilling_color;
    t_texture *texture;
}   t_map;

