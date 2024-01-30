# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: vvan-der <vvan-der@student.42.fr>            +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/03 18:04:48 by vvan-der      #+#    #+#                  #
#    Updated: 2024/01/30 14:29:20 by vvan-der      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
RM		= rm -rf
CC		= cc # changed it to cc
CFLAGS	= -Wall -Werror -Wextra#-g3 -fsanitize=address
OBJDIR	= libft_obj

SRCS	= ft_ato_double.c ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_iswhitespace.c ft_itoa.c ft_lutoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_pow.c ft_pow_fl.c ft_printf.c \
		ft_putchar_fd.c	ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putstrlen_fd.c ft_realloc.c ft_split.c ft_strchr.c ft_strcpy.c ft_strdup.c ft_striteri.c \
		ft_strjoin.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c \
		ft_substr.c ft_tolower.c ft_toupper.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_tolower_str.c ft_writoa.c get_next_line.c get_next_line_utils.c \

OBJS	= $(SRCS:%.c=$(OBJDIR)/%.o)

all:	$(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $^

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re test
