# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vvan-der <vvan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/21 16:24:27 by vvan-der      #+#    #+#                  #
#    Updated: 2023/09/19 13:08:21 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
NAME2	= minishell2
USER	= vvan-der
LIBFT	= libft
LIBS	= $(LIBFT)/libft.a #/usr/lib/x86_64-linux-gnu/libreadline.a
RM		= rm -rf
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra #-g -fsanitize=address
HEADERS	= #-I/usr/include/readline
L_FLAGS	= -lreadline #-L/usr/local/lib #-I/usr/local/include #-L/Users/$(USER)/.brew/opt/readline/lib 

SRCS	=	builtins.c \
			ft_shell_list_split.c \
			ft_shell_split.c \
			lexer.c \
			list_functions.c \
			main.c \
			utilities_01.c \

OBJDIR	= minishobjects

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

all: build_lib $(NAME)

build_lib: $(LIBFT)/Makefile
	$(MAKE) -C $(LIBFT)

$(LIBFT)/Makefile:
	git submodule init
	git submodule update

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(HEADERS) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(L_FLAGS) $(LIBS) -o $(NAME)

clean:	
	$(RM) $(OBJDIR)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)/$(LIBFT).a

re: fclean all

.PHONY: all, clean, fclean, re, build_lib
