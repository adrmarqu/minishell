# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrmarqu <adrmarqu@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/15 17:00:31 by adrmarqu          #+#    #+#              #
#    Updated: 2025/05/31 13:36:39 by adrmarqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB = ar rcs
RM = rm -f
CC = gcc
CCFLAGS = -Wall -Wextra -Werror

NAME = libft.a

SRC =	ft_memset.c ft_bzero.c ft_strlen.c ft_atoi.c ft_isdigit.c ft_isalpha.c\
ft_isprint.c ft_isascii.c ft_isalnum.c ft_memchr.c ft_memcpy.c ft_memcpy.c\
ft_memcmp.c ft_memmove.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c\
ft_strncmp.c ft_toupper.c ft_tolower.c ft_strnstr.c ft_strrchr.c ft_calloc.c\
ft_putchar_fd.c ft_putstr_fd.c ft_putnbr_fd.c ft_putendl_fd.c ft_substr.c\
ft_strjoin.c ft_strtrim.c ft_strmapi.c ft_itoa.c ft_split.c ft_striteri.c\
get_next_line.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c\
ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_isspace.c\
ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c print_split.c\
ft_free.c fd_printf.c flags.c ft_num.c init_flags.c putchar.c put_flags.c\
put_number.c ft_strndup.c ft_isempty.c

OBJ = $(SRC:.c=.o)

INCLUDE = libft.h

all: $(NAME)

$(NAME): $(OBJ)
	@$(LIB) $(NAME) $(OBJ)

%.o: %.c $(INCLUDE) Makefile
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	@$(RM) $(OBJ)
	@echo "---> Deleted '.o' of libft"

fclean: clean
	@$(RM) $(NAME)
	@echo "---> Deleted libft.a"

re: fclean all

.PHONY : all clean fclean re
