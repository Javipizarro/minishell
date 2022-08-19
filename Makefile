# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/19 11:24:00 by jpizarro          #+#    #+#              #
#    Updated: 2022/08/19 19:46:25 by jpizarro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re run show

NAME = minishell

SRCS =	builtins/builtiner.c												\
		builtins/cd.c														\
		builtins/echo.c														\
		builtins/env.c														\
		builtins/exit_shell.c												\
		builtins/export.c													\
		builtins/pwd.c														\
		builtins/unset.c													\
		env/add_env_link.c													\
		env/expand_var.c													\
		env/extract_env_var_name.c											\
		env/reset_envp.c													\
		env/set_env_list.c													\
		env/set_env_value.c													\
		parse/get_file_path.c												\
		parse/line_to_cmd.c													\
		parse/parse_cmds.c													\
		parse/parse_files.c													\
		parse/parser.c														\
		parse/tokenizer.c													\
		srcs/check_dir.c													\
		srcs/close_fds.c													\
		srcs/errors.c														\
		srcs/executer.c														\
		srcs/external.c														\
		srcs/free_stuff.c													\
		srcs/heredoc.c														\
		srcs/init_data.c													\
		srcs/kill_son.c														\
		srcs/minishell.c													\
		srcs/quotes.c														\
		srcs/search_env.c													\
		srcs/set_exit_status.c												\
		srcs/signal.c														\
		srcs/termios.c														\
		srcs/waiter.c

OBJS = $(SRCS:.c=.o)

LIBS = libft/libft.h #pipex/pipex.h

STATICS = $(LIBS:.h=.a)

CC = gcc

RM = rm -f

#CFLAGS = -Wall -Werror -Wextra
CFLAGS = -Wall -Werror -Wextra -g

LDFLAGS = -L/Users/$(USER)/.brew/opt/readline/lib

CPPFLAGS = -I/Users/$(USER)/.brew/opt/readline/include

LINKERS = -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(STATICS)
	@echo "Creating $@"
	@$(CC) $(CFLAGS) $(OBJS) $(STATICS) $(LINKERS) $(LDFLAGS) -o $@
	@echo "$@ is ready!"

%.o: %.c
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $(<:.c=.o)

$(STATICS):
#	cd libft/ && $(MAKE)
#	cd pipex/ && $(MAKE)
	@make -sC ./libft

clean:
	@echo "Cleaing up binary files"
	@$(RM) $(OBJS)
#	cd libft/ && $(MAKE) $@
#	cd pipex/ && $(MAKE) $@
	@make -sC ./libft $@

fclean: clean
	@echo "also $(NAME) and debug files"
	@$(RM) $(NAME) debug
	@$(RM) $(wildcard srcs/*.o)
	@$(RM) $(wildcard *.out)
#	cd libft/ && $(MAKE) $@
#	cd pipex/ && $(MAKE) $@
	@make -sC ./libft $@

re: fclean all

show:
	@echo "SRCS $(SRCS)"
	@echo "OBJS $(OBJS)"
	@echo "LIBS $(LIBS)"
	@echo "STATICS $(STATICS)"
	