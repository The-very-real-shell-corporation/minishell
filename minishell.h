/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 16:24:36 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/06 15:08:22 by vvan-der      ########   odam.nl         */
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
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <termios.h>
# include <sys/wait.h>
# include "libft/libft.h"

# define INFINITY	1
# define ERROR	1
# define SUCCESS 0
# define READ 0
# define WRITE 1
# define EXEC_ERR	10000

# define HD_PATH "heredoc_dir/heredoc.txt"

typedef struct s_data	t_data;

enum e_direction
{
	NONE,
	LEFT,
	RIGHT
};

enum e_position
{
	START,
	MIDDLE,
	END
};

typedef enum e_token
{
	B_CD = 0,
	B_ECHO,
	B_ENV,
	B_EXIT,
	B_EXPORT,
	B_PWD,
	B_UNSET,
	APPEND = 100,
	PIPE,
	RE_OUTPUT,
	HEREDOC,
	RE_INPUT,
	COMMAND = 200,
	DUMMY,
	FILENAME,
	INIT,
	WORD,
	STITCH
}	t_token;

typedef struct s_mlist
{
	char			**args;
	char			*str;
	t_token			token;
	struct s_mlist	*nx;
	struct s_mlist	*pv;
}	t_mlist;

struct s_data
{
	int		exit_status;
	char	**env_array;
	char	**path;
	char	**real_path;
	int		(*fn[7])(t_data *, char **);
	int		pipe_fds[2][2];
	pid_t	*pids;
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

void	carry_out_orders(t_data *data, t_mlist *pipelines, int i);
void	execute_command(t_data *data, char *directory, char **args);
void	execute_through_path(t_data *data, t_mlist *pipeline, char **path);
bool	run_builtins(t_data *data, t_mlist *pipeline);

/*	Expander (dollar)	*/

void	expand_dollar(t_data *data, char **str);
void	journey_to_alexpandria(t_data *data, t_mlist **input, char *str);

/*	Forking	*/

pid_t	create_fork(t_data *data);
void	wait_for_process(t_data *data, pid_t id, char *input);

/*	Initialization	*/

bool	get_input_and_parse(t_data *data);
void	initialize_data(t_data *data, char **envp);
bool	setup_redirections(t_data *data, t_mlist *pipeline);

/*	List functions (editing)	*/

void	clear_mlist(t_mlist **list);
t_mlist	*copy_node(t_data *data, t_mlist *node);
void	delete_node(t_mlist **node);
void	insert_node(t_mlist *node1, t_mlist *node2, t_mlist *new);
t_mlist	*new_node(t_data *data, char *word, char **args, t_token tolkien);
void	node_addback(t_mlist **list, t_mlist *new_node);
void	replace_node(t_data *data, t_mlist *node, char *input);
void	unlink_node(t_mlist *node);

/*	List functions (navigation)	*/

t_mlist	*find_input(t_mlist *env, char *input);
bool	go_to_token(t_mlist **list, t_token tolkien);
size_t	list_size(t_mlist *list, t_token tolkien);
size_t	list_size_redirection(t_mlist *list);
t_mlist	*node_first(t_mlist *list);
t_mlist	*node_last(t_mlist *list);
size_t	count_tokens(t_mlist *list, t_token tolkien);

/*	List functions (utility)	*/

int		print_env(t_mlist *list);
void	print_list(t_mlist *list);

/*	Lexer	*/

void	expansion_pack(t_data *data, char *input);
bool	first_last(char *str, char c);
int		ft_ministrcmp(char *str1, char *str2);
char	*mini_shubstr(t_data *data, char *str, int len);
void	tokenize_list(t_data *data, t_mlist *in);

/*	Parser functions	*/

void	copy_environment(t_data *data, t_mlist **env, char **envp);
t_mlist	*ft_special_split(t_data *data, char *input);

/* Pipes */

void	build_pipelines(t_data *data, t_mlist *input, t_mlist **pipelines);
void	close_main_fds(int pipe_fds[2][2]);
void	make_pipes_pipe(t_data *data, int pipe_fds[2][2]);
void	duplicate_fd(t_data *data, int old, int new);
pid_t	fork_process(t_data *data, t_mlist *pipelines);
void	open_pipe(t_data *data, int pipes);
void	whatsup_doc(t_data *data, char *delim);

/*	Signals	*/

void	set_signals(void);
void	signal_int_handler(int sig);
void	signals_for_kids(void);
void	unset_signals(void);

/*	String manipulations	*/

void	dollar_in_env(t_data *data, char *input, char **env_string);
char	*envp_string(t_data *data, char *input);
char	*remake_str(char *original, int start, int len, char *newpart);

/*	Utility functions	*/

bool	everythingiswhitespace(char *str);
void	exit_error(t_data *data, char *msg);
bool	is_builtin(t_token tolkien);
bool	is_redirection(t_token tolkien);
void	lexer_error(t_data *data, char *msg, char *token);
char	**list_to_array(t_data *data, t_mlist *list);
void	print_2d_charray(char **array);
int		ptr_array_size(void **array);
bool	is_quote(char c);
void	print_debug(t_mlist *list);
bool	contains_redirections(t_mlist *list);

#endif
