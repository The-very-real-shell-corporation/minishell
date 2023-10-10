/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/11 16:30:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/10 18:09:27 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <stdarg.h>
# include "../minishell.h"

typedef struct s_data t_data;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

/* Character functions */

int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_iswhitespace(int c);
int			ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *c, int fd);
void		ft_putnbr_fd(int c, int fd);
void		ft_putstr_fd(char *c, int fd);
int			ft_tolower(int c);
int			ft_toupper(int c);

/* Memory functions */

void		ft_bzero(void *str, size_t n);
void		*ft_calloc(size_t count, size_t size);
char		*ft_realloc(t_data *data, char *str, size_t size);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);

/* Math functions */

long double	ft_ato_double(const char *str);
int			ft_atoi(const char *str);
char		*ft_itoa(int n);
long double	ft_pow_fl(long double number, int power);
long long	ft_pow(int number, int power);
int			ft_writoa(int n);
int			ft_lutoa(size_t args, int base, int b);

/* List functions */

void		ft_lstadd_front(t_list **lst, t_list *new);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(void *content);
int			ft_lstsize(t_list *lst);
int			ft_printf(const char *input, ...);

/* String functions */

char		**ft_split(char *s, char c);
char		*ft_strchr(const char *str, int c);
void		ft_strcpy(char *dst, char *src);
char		*ft_strdup(char *s1);
char		*ft_strdup2(t_data *data, char *s1);
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strjoin(const char *s1, const char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(char *s1, char *set);
char		*ft_substr(const char *s, unsigned int start, size_t len);
char		*ft_tolower_str(char *str);
int			ft_putstrlen_fd(char *s, int fd);

#endif
