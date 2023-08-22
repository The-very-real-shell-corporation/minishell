# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vvan-der <vvan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/21 16:24:27 by vvan-der      #+#    #+#                  #
#    Updated: 2023/08/22 16:08:26 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
LIBFT	= libft
RM		= rm -rf
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra #-g3 -fsanitize=address
L_FLAGS	= -L/usr/local/lib -I/usr/local/include -lreadline
SRCS	= main.c

OBJDIR	= minishobjects

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

all: build_lib $(NAME)

build_lib: $(LIBFT)/Makefile
	$(MAKE) -C $(LIBFT)

$(LIBFT)/Makefile:
	git submodule init
	git submodule update

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(L_FLAGS) $(OBJS) -o $(NAME)

clean:	
	$(RM) $(OBJDIR)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)/$(LIBFT).a

re: fclean all

.PHONY: all, clean, fclean, re, build_lib
