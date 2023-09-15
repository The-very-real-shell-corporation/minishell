# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vvan-der <vvan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/21 16:24:27 by vvan-der      #+#    #+#                  #
#    Updated: 2023/09/15 14:45:31 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
USER	= vvan-der
LIBFT	= libft
RM		= rm -rf
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -I/Users/$(USER)/.brew/opt/readline/include -g -fsanitize=address
L_FLAGS	= -L/usr/local/lib -I/usr/local/include -L/Users/$(USER)/.brew/opt/readline/lib  -lreadline
SRCS	= builtins.c main.c

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
	$(CC) $(L_FLAGS) $(CFLAGS) $(OBJS) $(LIBFT)/$(LIBFT).a  -o $(NAME)

clean:	
	$(RM) $(OBJDIR)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)/$(LIBFT).a

re: fclean all

.PHONY: all, clean, fclean, re, build_lib
