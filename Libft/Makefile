CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = ft_isdigit.c ft_memcpy.c ft_bzero.c ft_strdup.c \
        ft_substr.c ft_calloc.c ft_isprint.c ft_memmove.c ft_strjoin.c \
        ft_strncmp.c ft_tolower.c ft_isalnum.c ft_itoa.c ft_memset.c \
        ft_strlcat.c ft_strnstr.c ft_toupper.c ft_isalpha.c ft_memchr.c \
        ft_split.c ft_strlcpy.c ft_strrchr.c ft_atoi.c ft_isascii.c \
        ft_memcmp.c ft_strchr.c ft_strlen.c ft_strtrim.c ft_strmapi.c \
        ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
        ft_putnbr_fd.c ft_strstr.c get_next_line.c ft_strcpy.c ft_strndup.c 
SRCS_BN = ft_lstadd_back_bonus.c ft_lstadd_front_bonus.c ft_lstclear_bonus.c \
           ft_lstdelone_bonus.c ft_lstiter_bonus.c ft_lstlast_bonus.c \
           ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstsize_bonus.c

OBJS = $(SRCS:.c=.o)
OBJS_BN = $(SRCS_BN:.c=.o)

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $(OBJS)

bonus: $(OBJS) $(OBJS_BN)
	@ar rcs $(NAME) $(OBJS) $(OBJS_BN)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS) $(OBJS_BN)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
