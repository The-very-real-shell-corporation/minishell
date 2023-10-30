# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vvan-der <vvan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/21 16:24:27 by vvan-der      #+#    #+#                  #
#    Updated: 2023/10/30 17:22:36 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
NAME2	= minishell2
USER	= vvan-der
LIBFT	= libft
LIBS	= $(LIBFT)/libft.a #/usr/lib/x86_64-linux-gnu/libreadline.a
RM		= rm -rf
CC		= cc # changed it to cc
CFLAGS	= -Wall -Werror -Wextra -g #-fsanitize=address
HEADERS	= #-I/usr/include/readline
L_FLAGS	= -lreadline #-L/usr/local/lib #-I/usr/local/include #-L/Users/$(USER)/.brew/opt/readline/lib

SRCS	=	builtins_A_to_E.c \
			builtins_F_to_Z.c \
			clean_up.c \
			environment.c \
			fill_in_nodes.c \
			find_the_path.c \
			ft_ministrncmp.c \
			ft_shell_list_split.c \
			lexer.c \
			list_functions.c \
			main.c \
			utilities_01.c \

OBJDIR	= shobjects

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(LIBS):
	$(MAKE) -C $(LIBFT)

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) $(HEADERS) -o $@ $^

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(NAME): $(LIBS) $(OBJDIR) $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) $(L_FLAGS) $(LIBS) -o $(NAME)

clean:	
	$(RM) $(OBJDIR)
	make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	$(RM) $(LIBFT)/$(LIBFT).a

re: fclean all

.PHONY: all, clean, fclean, re, build_lib
