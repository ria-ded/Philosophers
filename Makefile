# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mdziadko <mdziadko@student.42warsaw.pl>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/19 22:20:09 by mdziadko          #+#    #+#              #
#    Updated: 2025/09/16 10:01:38 by mdziadko         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# **************************************************************************** #
# 								   VARIABLES								   #
# **************************************************************************** #

NAME		= philo
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g3 #-fsanitize=address
AR			= ar rcs
RM			= rm -f
FLAGS		= -pthread

# Directories
OBJ_DIR			= obj

# **************************************************************************** #
# 									FILES									   #
# **************************************************************************** #

SRCS		= main.c \
				init.c \
				simulation.c \
				routine.c \
				monitor.c \
				print.c \
				help.c \
				cleanup.c
OBJS		= $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
HEADERS		= philo.h

# **************************************************************************** #
# 									RULES									   #
# **************************************************************************** #

all: $(NAME) 

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(FLAGS) -o $(NAME)

$(OBJ_DIR)/%.o: %.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(FLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re