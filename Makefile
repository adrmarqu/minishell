# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adrmarqu <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/17 13:59:30 by adrmarqu          #+#    #+#              #
#    Updated: 2025/08/02 17:39:31 by adrmarqu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Werror -Wextra -fsanitize=address
READLINE = -lreadline
#-Lreadline -lhistory -lncurses
#gcc srcs/*.c libft/*.c srcs/parser/*.c srcs/built-ins/*.c -lreadline

LIBFT = ./libft/libft.a

SRC = main.c utils.c init.c command.c split_tokens.c token.c ft_free_parser.c \
	  print.c free.c expand.c expand_utils.c expand_wildcard.c wildcard_utils.c \
	  split_wildcard.c check_token.c build_cmd.c create.c execute_tree.c execute.c \
	  cd_mini.c env_mini.c export_mini.c unset_mini.c echo_mini.c exit_mini.c \
	  pwd_mini.c execute_utils.c export_var.c export_utils.c export_modify.c \
	  print2.c cd_expand.c redir.c utils2.c heredoc.c

SRC_D = ./srcs/
BLT_D = ./srcs/built-ins/
PAR_D = ./srcs/parser/

OBJ_F = $(SRC:.c=.o)
OBJ_D = ./objects/
OBJ = $(addprefix $(OBJ_D), $(OBJ_F))

DEP_F = $(SRC:.c=.d)
DEP_D = ./dependencies/
DEP = $(addprefix $(DEP_D), $(DEP_F))

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(READLINE) $(LIBFT) -o $(NAME)

$(OBJ_D)%.o: $(SRC_D)%.c Makefile | $(OBJ_D) $(DEP_D)
	$(CC) $(CFLAGS) -MMD -MF $(DEP_D)$*.d -c $< -o $@

$(OBJ_D)%.o: $(BLT_D)%.c Makefile | $(OBJ_D) $(DEP_D)
	$(CC) $(CFLAGS) -MMD -MF $(DEP_D)$*.d -c $< -o $@

$(OBJ_D)%.o: $(PAR_D)%.c Makefile | $(OBJ_D) $(DEP_D)
	$(CC) $(CFLAGS) -MMD -MF $(DEP_D)$*.d -c $< -o $@

$(LIBFT):
	make -C libft --no-print-directory

$(OBJ_D):
	mkdir -p $(OBJ_D)

$(DEP_D):
	mkdir -p $(DEP_D)

readline:
	make -C readline

.rl_config:
	echo "READLINE WILL BE CONFIGURED";
	cd readline && ./configure;
	touch .rl_config

-include $(DEP)

clean:
	make clean -C libft --no-print-directory
	rm -rf $(OBJ_D) $(DEP_D)

fclean: clean
	make fclean -C libft --no-print-directory
	rm -rf $(NAME)
	rm -rf .rl_config

re: fclean all

.PHONY: all clean fclean re readline
