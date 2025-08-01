#pragma once

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "../Libft/libft.h"
#include <fcntl.h>
#include <stdbool.h>


#define ERROR_INVALID_MAP "\033[1;31mError:\nInvalid map structure.\033[0m \n"
#define ERROR_INVALID_BORDER_LINES "\033[1;31mError\nMap border lines are invalid.\033[0m \n"
#define ERROR_INVALID_BORDER_COLUMNS "\033[1;31mError\nMap border columns are invalid.\033[0m\n"
#define ERROR_FLOOD_FILL_FAIL "\033[1;31mError\nFlood fill failed — map not enclosed properly.\033[0m\n"
#define ERR_EMPTY_PATH "\033[1;31mError\nEmpty path for texture\n\033[0m"
#define ERR_DUP_NORTH "\033[1;31mError\nDuplicate North texture path\n\033[0m"
#define ERR_DUP_SOUTH "\033[1;31mError\nDuplicate South texture path\n\033[0m"
#define ERR_DUP_EAST "\033[1;31mError\nDuplicate East texture path\n\033[0m"
#define ERR_DUP_WEST "\033[1;31mError\nDuplicate West texture path\n\033[0m"
#define ERR_DUP_CEILING "\033[1;31mError\nDuplicate Ceilling color\n\033[0m"
#define ERR_DUP_FLOOR "\033[1;31mError\nDuplicate Floor color\n\033[0m"
#define ERR_EXTRA_CHAR "\033[1;31mError\nExtra characters after color definition\n\033[0m"
#define ERR_OUT_OF_RANGE "\033[1;31mError\nRGB color values out of range [0-255]\n\033[0m"
#define ERR_INVALID_PATH "\033[1;31mError\nInvalid path to textures\n\033[0m"
#define ERROR_INVALID_CHARACTERS "\033[1;31mError\nInvalid characters or player count in map.\033[0m\n"

#define INVALID_ARGS "\033[0;31mError\nInvalid Arguments\n\033[0m"
#define INVALID_FILE "\033[0;31mError\nInvalid File\n\033[0m"
#define OPEN_FILE_ERROR "\033[0;31mError\nCannot Open FILE\n\033[0m"
#define INVALID_MAP "\033[0;31mError\nInvalid Map\n\033[0m"
#define INVALID_ORDER "\033[0;31mError\nInvalid Order\n\033[0m"



#define SLASH '/'
#define TRUE 1
#define FALSE 0
#define SPACE ' '
#define COMMA ','
#define EXTENSION ".cub"
#define DOT '.'
#define NEW_LINE '\n'

#define WALL '1'
#define EMPTY '0'
#define PLAYER_N 'N'
#define PLAYER_S 'S'
#define PLAYER_W 'W'
#define PLAYER_E 'E'






typedef struct s_color
{
    int r;
    int g;
    int b;
    int is_set_f;
    int is_set_c;
}   t_color;



typedef struct s_texture
{
    char *north;
    char *south;
    char *west;
    char *east;
    char **map;
    int start;
    int x_player;
    int y_player;
    char position_player;
}   t_texture;



typedef struct s_map
{
    char **map2D;
    int fd;
    int read_bytes;
    t_color f_color;
    t_color c_color;
    t_texture *texture;
}   t_map;

