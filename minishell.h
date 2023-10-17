/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:24:36 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/17 19:04:25 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/types.h>
# include <termios.h>
# include "libft/libft.h"

typedef struct s_data	t_data;

#define INFINITY 1

#define LEFT 0
#define RIGHT 1

typedef enum e_token
{
	INITIALIZED,
	PIPE,
	RE_INPUT,
	RE_OUTPUT,
	HEREDOC,
	APPEND,
	WORD,
	COMMAND,
	DOLLAR_SIGN,
	STRING_SQ,
	STRING_DQ,
	BUILT_IN,
	// SINGLE_QUOTE,
	// DOUBLE_QUOTE
}	t_token;

typedef struct s_mlist
{
	char			*str;
	t_token			token;
	struct s_mlist	*nx;
	struct s_mlist	*pv;
}	t_mlist;

struct s_data
{
	char	**path;
	t_mlist	*env;
	t_mlist	*sorted_env;
	t_mlist	*input;
};

/*	Built-ins	*/

void	cd_builtin(char *path); //done
void	echo_builtin(char *msg, char *flag);
void	env_builtin(t_data *data); //done
void	exit_builtin(char *msg);
void	export_builtin(t_data *data, char *input);
void	pwd_builtin(t_data *data); //done
// void	unset_builtin(t_data *data, char *msg);

/*	List functions	*/

void	clear_mlist(t_mlist **list);
t_mlist	*new_node(t_data *data, char *word);
t_mlist	*node_first(t_mlist *list);
t_mlist	*node_last(t_mlist *list);
void	insert_node(t_mlist **node1, t_mlist **node2, t_mlist *new);
void	node_addback(t_mlist **list, t_mlist *new_node);
t_mlist	*ft_shell_list_split(t_data *data, char *input);
bool	find_input(t_data *data, char *input);
void	print_list(t_mlist *list);
void	print_env(t_mlist *list);

/*	Lexer	*/

int		ft_ministrncmp(char *str1, char *str2);
void	analyze_input(t_data *data, t_mlist *input);
void	tokenize_list(t_mlist *list);
char	*make_word(t_data *data, char *str, int start, int end);
int		assign_token(char *str);

/*	Parser functions	*/

char	**ft_shell_split(char *s);
void	get_path_ready(t_data *data);
void	copy_environment(t_data *data, char **envp);
void	sort_environment(t_data *data);

/*	Utility functions	*/

void	clean_up(t_data *data);
void	exit_error(t_data *data, char *msg);
void	print_2Dcharray(char **array);

#endif
