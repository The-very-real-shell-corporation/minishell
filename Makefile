# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vvan-der <vvan-der@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/08/21 16:24:27 by vvan-der      #+#    #+#                  #
#
#    Updated: 2023/12/27 18:59:25 by lotse         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= minishell
LIBFT	= libft
LIBS	= $(LIBFT)/libft.a
RM		= rm -rf
CC		= cc
CFLAGS	= -Wall -Werror -Wextra #-g
L_FLAGS	= -lreadline

SRCS	=	alexer.c \
			alexer_chexer.c \
			alexpander_the_great.c \
			builtin_cd.c \
			builtin_echo.c \
			builtin_env.c \
			builtin_exit.c \
			builtin_export.c \
			builtin_pwd.c \
			builtin_unset.c \
			clean_up.c \
			environment.c \
			errors.c \
			executils.c \
			execution.c \
			exit_process.c \
			expand_dollar.c \
			forks.c \
			ft_special_split.c \
			heredoc.c \
			initialize.c \
			journey_to_alexpandria.c \
			list_adding.c \
			list_navigate.c \
			list_navigate2.c \
			list_printing.c \
			list_removal.c \
			main.c \
			pipe_utils.c \
			pipes.c \
			redirections.c \
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
	$(CC) -c $(CFLAGS) -o $@ $^

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
