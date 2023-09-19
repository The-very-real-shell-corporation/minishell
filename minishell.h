/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:24:36 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/19 13:31:10 by vvan-der      ########   odam.nl         */
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
# include "libft/libft.h"

typedef enum e_token
{
	INITIALIZED,
	PIPE,
	REDIRECT,
	APPEND,
	
}	t_token;

typedef struct s_mlist
{
	char			*str;
	t_token			token;
	struct t_mlist	*nx;
	struct t_mlist	*pv;
}	t_mlist;

/*	Built-ins	*/

void	pwd_builtin(void);
void	echo_builtin(char *msg, char *flag);
void	cd_builtin(char *path);
void	env_builtin(char **envp);

/*	List functions	*/

void	clear_mlist(t_mlist **list);
t_mlist	*new_node(char *word);
t_mlist	*node_last(t_mlist *list);
void	node_addback(t_mlist **list, t_mlist *new_node);
t_mlist	*ft_shell_list_split(char *input);

/*	Lexer	*/

void	analyze_input(char **input);


/*	Parser functions	*/

char	**chop_string(char *input);
void	parse_input(char **in, char *input);
char	**ft_shell_split(char *s);

/*	Utility functions	*/

void	free_2D(char **input);
void	exit_error(char *msg);

#endif