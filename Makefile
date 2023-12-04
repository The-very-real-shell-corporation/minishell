# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vvan-der <vvan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/21 16:24:27 by vvan-der      #+#    #+#                  #
#    Updated: 2023/12/04 18:13:18 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
NAME2	= minishell2
USER	= vvan-der
LIBFT	= libft
LIBS	= $(LIBFT)/libft.a #/usr/lib/x86_64-linux-gnu/libreadline.a
RM		= rm -rf
CC		= cc # changed it to cc
CFLAGS	= -Wall -Werror -Wextra -g
#CFLAGS	+= -fsanitize=address
HEADERS	= #-I/usr/include/readline
L_FLAGS	= -lreadline #-L/usr/local/lib #-I/usr/local/include #-L/Users/$(USER)/.brew/opt/readline/lib

SRCS	=	alexer.c \
			alexpander_the_great.c \
			builtins_A_to_E.c \
			builtins_F_to_Z.c \
			clean_up.c \
			environment.c \
			expand_dollar.c \
			find_the_path.c \
			ft_special_split.c \
			initialize.c \
			list_editing.c \
			list_navigate.c \
			list_printing.c \
			main.c \
			signals.c \
			string_functions.c \
			string_nav.c \
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
