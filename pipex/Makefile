# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jpizarro <jpizarro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/19 11:24:00 by jpizarro          #+#    #+#              #
#    Updated: 2022/05/07 19:13:43 by jpizarro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY: all clean debug fclean re run show

NAME = pipex

SRCS =	srcs/pipex_data_init.c		\
		srcs/error_exit.c			\
		srcs/exec_cmd.c				\
		srcs/exec_cmds.c			\
		srcs/get_env_path.c			\
		srcs/get_files.c			\
		srcs/get_path.c				\
		srcs/perror_exit.c			\
		srcs/pipex.c				\
		srcs/check_argc.c

OBJS = $(SRCS:.c=.o)

LIBS = ../libft/libft.h

STATICS = $(LIBS:.h=.a)

CC = gcc

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME): $(OBJS) $(STATICS)
	@echo "Creating $@"
	@$(CC) $(CFLAGS) $(OBJS) $(STATICS) -o $@
	@echo "$@ is ready!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

#$(STATICS):
#	cd ../libft/ && $(MAKE)

clean:
	@echo "Cleaing up binary files"
	@$(RM) $(OBJS)
#	cd ../libft/ && $(MAKE) $@

fclean: clean
	@echo "also $(NAME), debug files"
	@$(RM) $(NAME) debug
	@$(RM) $(wildcard srcs/*.o)
	@$(RM) $(wildcard *.out)
#	cd ../libft/ && $(MAKE) $@

re: fclean all

#rebonus: fclean bonus

debug: fclean $(OBJS) #$(STATICS)
	@echo "Creating $@ file"
#	@$(CC) -g $(OBJS) $(STATICS) -o $@
	@$(CC) -g $(OBJS) -o $@
	@echo "$@ is ready!"

show:
	@echo "SRCS $(SRCS)"
	@echo "OBJS $(OBJS)"
	