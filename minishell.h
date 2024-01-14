/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:24:36 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/14 16:11:10 by vincent       ########   odam.nl         */
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
# include <fcntl.h>
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

# define INFINITY	1
# define EXEC_ERR	10000

# define LEFT 0
# define RIGHT 1

typedef enum e_token
{
	B_CD,
	B_ECHO,
	B_ENV,
	B_EXIT,
	B_EXPORT,
	B_PWD,
	B_UNSET,
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
	UNDERSCORE,
	DUMMY
}	t_token;

typedef struct s_mlist
{
	char			**pipeline;
	char			*str;
	t_token			token;
	struct s_mlist	*nx;
	struct s_mlist	*pv;
}	t_mlist;

struct s_data
{
	int		exit_status;
	char	**argv;
	char	**env_array;
	char	**delim;
	char	**path;
	char	**real_path;
	char	*cwd;
	char	*line;
	int		(*fn[7])(t_data *, char **);
	int		pipe_fds[2][2];
	pid_t	*pids;
	t_mlist	*heredoc;
	t_mlist	*env;
	t_mlist	*input;
	t_mlist	*pipelines;
};

/*	Built-ins	*/

int		cd_builtin(t_data *data, char **args);
int		echo_builtin(t_data *data, char **args);
int		env_builtin(t_data *data, char **args);
int		exit_builtin(t_data *data, char **args);
int		export_builtin(t_data *data, char **args);
int		pwd_builtin(t_data *data, char **args);
int		unset_builtin(t_data *data, char **args);

/*	Clean-up	*/

void	clean_up(t_data *data);
void	free_and_null(void **variable);
void	free_2d_(void ***input);
void	loop_clean(t_data *data);

/*	Environment stuff	*/

void	change_env_var(t_data *data, char *var, char *new_value);
t_mlist	*sort_environment(t_data *data, t_mlist *env);

/*	Execution	*/

void	execute(t_data *data, t_mlist *pipelines, pid_t *pids);
void	fork_stuff(t_data *data);
bool	run_builtins(t_data *data, t_mlist *pipeline);
void	execute_command(t_data *data, char *directory, char **args);
void	search_the_path(t_data *data, t_mlist *pipeline, char **path);

/*	Expander (dollar)	*/

void	expand_dollar(t_data *data, char **str);

/*	Forking	*/

pid_t	create_fork(t_data *data);
void	wait_for_process(t_data *data, pid_t id);

/*	Heredoc	*/

void	whatsup_doc(t_data *data, t_mlist *input);

/*	Initialization	*/

void	parse_input(t_data *data, char *input);
void	initialize_data(t_data *data, char **envp);

/*	List functions (editing)	*/

void	clear_mlist(t_mlist **list);
t_mlist	*new_node(t_data *data, char *word, char **args, t_token tolkien);
void	delete_node(t_mlist *node);
void	insert_node(t_mlist *node1, t_mlist *node2, t_mlist *new);
void	node_addback(t_mlist **list, t_mlist *new_node);
void	replace_node(t_data *data, t_mlist *node, char *input);
void	unlink_node(t_mlist *node);

/*	List functions (navigation)	*/

t_mlist	*node_first(t_mlist *list);
t_mlist	*node_last(t_mlist *list);
t_mlist	*find_input(t_mlist *env, char *input);
bool	go_to_token(t_mlist **list, t_token tolkien);
size_t	list_size(t_mlist *list, t_token tolkien);

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

/*	Parser functions	*/

t_mlist	*ft_special_split(t_data *data, char *input);
void	get_path_ready(t_data *data);
void	copy_environment(t_data *data, char **envp);

/* Pipes */

void	build_pipeline(t_data *data, t_mlist *input, t_token tolkien);
void	copy_pipe_fds(t_data *data, int pipes[2][2]);
pid_t	fork_pipe(t_data *data, t_mlist *pipelines);
void	open_pipe(t_data *data, int pipes);
void	close_extra_fds(int pipe_fds[2][2]);
void	close_main_fds(int pipe_fds[2][2]);

/*	Signals	*/

void	set_signals(void);
void	unset_signals(void);
void	signals_for_kids(void);
void	signal_int_handler(int sig);

/*	String manipulations	*/

char	*envp_string(t_data *data, char *input);
char	*remake_str(char *original, int start, int len, char *newpart);
void	dollar_in_env(t_data *data, char *input, char **env_string);

/*	Utility functions	*/

void	exit_error(t_data *data, char *msg);
void	print_2d_charray(char **array);
char	**list_to_array(t_data *data, t_mlist *list, t_token tolkien);
bool	everythingiswhitespace(char *str);
int		ptr_array_size(void **array);

#endif
