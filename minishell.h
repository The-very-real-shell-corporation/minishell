/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:24:36 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/04 18:17:29 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdbool.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <stdint.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <termios.h>
# include <sys/wait.h>
# include "libft/libft.h"

typedef struct s_data	t_data;

#define INFINITY 1

#define LEFT 0
#define RIGHT 1

typedef enum e_token
{
	INITIALIZED,
	PIPE,
	PIPELINE,
	RE_INPUT,
	RE_OUTPUT,
	HEREDOC,
	HEREDOC_DELIM,
	APPEND,
	WORD,
	COMMAND,
	ECHO_FLAG,
	B_CD,
	B_ECHO,
	B_ENV,
	B_EXIT,
	B_EXPORT,
	B_PWD,
	B_UNSET
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
	int		exit_status;
	char	**path;
	char	**real_path;
	char	**argv;
	char	**env_array;
	char	*cwd;
	char	*line;
	t_mlist	*env;
	t_mlist	*sorted_env;
	t_mlist	*input;
};

/*	Built-ins	*/

int		cd_builtin(t_data *data, char *path);
int		echo_builtin(char *msg, bool n_flag);
int		env_builtin(t_data *data);
int		exit_builtin(t_data *data, char *msg);
int		export_builtin(t_data *data, char *input);
int		pwd_builtin(t_data *data);
int		unset_builtin(t_data *data, char *input);

/*	Environment stuff	*/

void	change_env_var(t_data *data, char *var, char *new_value);

/*	Expander (dollar)	*/

void	expand_dollar(t_data *data, char **str);

/*	Initialization	*/

void	parse_input(t_data *data, char *input);
void	initialize_data(t_data *data, char **envp);
// void	init_sigint(struct sigaction *sa);
// void	init_sigquit(struct sigaction *sa);

/*	List functions (editing)	*/

void	clear_mlist(t_mlist **list);
t_mlist	*new_node(t_data *data, char *word);
void	delete_node(t_mlist *node);
void	insert_node(t_mlist **node1, t_mlist **node2, t_mlist *new);
void	node_addback(t_mlist **list, t_mlist *new_node);
void	replace_node(t_data *data, t_mlist *node, char *input);
void	unlink_node(t_mlist *node);

/*	List functions (navigation)	*/

t_mlist	*node_first(t_mlist *list);
t_mlist	*node_last(t_mlist *list);
t_mlist	*find_input(t_mlist *env, char *input);
size_t	list_size(t_mlist *list);

/*	List functions (utility)	*/

void	print_list(t_mlist *list);
int		print_env(t_mlist *list);

/*	Lexer	*/

void	expansion_pack(t_data *data, char *input);
bool	first_last(char *str, char c);
int		ft_ministrcmp(char *str1, char *str2);
void	analyze_input(t_data *data);
void	tokenize_list(t_mlist *list);
char	*mini_shubstr(t_data *data, char *str, int len);
int		assign_token(char *str);

/*	Pathfinding	*/

bool	search_the_path(t_data *data, char **path);

/*	Parser functions	*/

char	**ft_shell_split(char *s);
t_mlist	*ft_special_split(t_data *data, char *input);
t_mlist	*ft_shell_list_split(t_data *data, char *input);
void	get_path_ready(t_data *data);
void	copy_environment(t_data *data, char **envp);
void	sort_environment(t_data *data);

/*	Signals	*/

void	set_signals(void);
void	unset_signals(void);
void	signals_for_kids(void);
void	signal_int_handler(int sig);

/*	String manipulations	*/

char	*env_string(t_data *data, char *input);
char	*partially_merge_str(char *original, int start, int len, char *newpart);
void	dollar_in_env(t_data *data, char *input, char **env_string);

/*	Utility functions	*/

void	clean_up(t_data *data);
void	loop_clean(t_data *data);
void	free_and_null(void *variable);
void	free_2d_(char **input);
void	exit_error(t_data *data, char *msg);
void	print_2d_charray(char **array);
char	**list_to_array(t_data *data ,t_mlist *list);
bool	everythingiswhitespace(char *str);

#endif
