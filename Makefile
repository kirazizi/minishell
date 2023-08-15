# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbzizal <sbzizal@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/26 10:21:54 by sbzizal           #+#    #+#              #
#    Updated: 2023/08/15 18:09:03 by sbzizal          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CFLAGS = -Wall -Wextra -Werror

CFILES = minishell.c\
./builtins/ft_cd.c ./builtins/ft_pwd.c ./builtins/ft_echo.c ./builtins/ft_export.c ./builtins/ft_export_join.c \
./builtins/ft_cd_utls.c ./builtins/ft_cd_utls1.c ./builtins/ft_unset_utls.c ./builtins/ft_env_utls.c \
./builtins/ft_export_pars.c ./builtins/ft_export_print.c ./builtins/ft_export_update.c \
./builtins/ft_unset.c ./builtins/ft_exit.c ./builtins/ft_env.c ./builtins/ft_export_utls.c \
./execut/exec_part.c ./execut/exec_utls.c ./execut/exec.c ./execut/execut_singl.c ./execut/shell_lvl.c \
./execut/signal.c ./execut/my_heredoc.c ./execut/my_expand.c \
./parsing/expand.c ./parsing/ft_check_syntax.c ./parsing/ft_check_token.c ./parsing/ft_spli.c \
./parsing/ft_split_suite2.c ./parsing/parsing_v1.c ./parsing/parsing_v2.c ./parsing/redirection.c \
./parsing/remove_spac_q.c ./parsing/suit_expand.c ./parsing/suit_redirection.c ./parsing/suit_remove_s_q.c \
./parsing/suite2_redirection.c ./parsing/toknization.c ./parsing/ft_check_syntax2.c \
./utls_minishell/free_all.c ./utls_minishell/ft_lstnew.c ./utls_minishell/mini_utilise.c ./utls_minishell/main_utls2.c \
./utls_minishell/utls_libft.c ./utls_minishell/utls_mini_1.c ./utls_minishell/utls_mini_2.c \
./utls_minishell/utls_mini_3.c ./utls_minishell/utls_mini_4.c ./utls_minishell/main_utils.c \


OFILES = ${CFILES:.c=.o}

all: $(NAME)

$(NAME): $(OFILES) minishell.h
	$(CC) $(CFLAGS) $(OFILES) -o $(NAME) -lreadline -L/Users/sbzizal/.brew/opt/readline/lib

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -I/Users/sbzizal/.brew/opt/readline/include -c $< -o $@

clean:
	rm -f $(OFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
