# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/19 11:24:00 by jpizarro          #+#    #+#              #
#    Updated: 2022/05/11 13:41:17 by jpizarro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean fclean re run show

NAME = minishell

SRCS =	$(wildcard srcs/*.c) $(wildcard builtins/*.c)

OBJS = $(SRCS:.c=.o)

LIBS = libft/libft.h #pipex/pipex.h

STATICS = $(LIBS:.h=.a)

CC = gcc

RM = rm -f

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
	@make -sC ./pipex

clean:
	@echo "Cleaing up binary files"
	@$(RM) $(OBJS)
#	cd libft/ && $(MAKE) $@
#	cd pipex/ && $(MAKE) $@
	@make -sC ./libft $@
	@make -sC ./pipex $@

fclean: clean
	@echo "also $(NAME) and debug files"
	@$(RM) $(NAME) debug
	@$(RM) $(wildcard srcs/*.o)
	@$(RM) $(wildcard *.out)
#	cd libft/ && $(MAKE) $@
#	cd pipex/ && $(MAKE) $@
	@make -sC ./libft $@
	@make -sC ./pipex $@

re: fclean all

show:
	@echo "SRCS $(SRCS)"
	@echo "OBJS $(OBJS)"
	@echo "LIBS $(LIBS)"
	@echo "STATICS $(STATICS)"
	