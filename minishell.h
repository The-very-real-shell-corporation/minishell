/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:24:36 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/10 18:32:02 by vvan-der      ########   odam.nl         */
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
# include "libft/libft.h"

typedef struct s_data	t_data;

#define INFINITY 1

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
	t_mlist	*input;
};

/*	Built-ins	*/

void	pwd_builtin(void);
void	echo_builtin(char *msg, char *flag);
void	cd_builtin(char *path);
void	env_builtin(char **envp);

/*	List functions	*/

void	clear_mlist(t_mlist **list);
t_mlist	*new_node(t_data *data, char *word);
t_mlist	*node_last(t_mlist *list);
void	node_addback(t_mlist **list, t_mlist *new_node);
t_mlist	*ft_shell_list_split(t_data *data, char *input);

/*	Lexer	*/

void	analyze_input(t_mlist *input);
void	tokenize_list(t_mlist *list);
char	*make_word(t_data *data, char *str, int start, int end);
int		assign_token(char *str);

/*	Parser functions	*/

char	**ft_shell_split(char *s);
void	get_path_ready(t_data *data);

/*	Utility functions	*/

void	clean_up(t_data *data);
void	exit_error(t_data *data, char *msg);
void	print_list(t_mlist *list);
void	print_2Dcharray(char **array);

#endif