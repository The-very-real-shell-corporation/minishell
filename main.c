/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/31 18:19:11 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_data *data, char *msg)
{
	clean_up(data);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	initialize_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->path = NULL;
	data->path2 = NULL;
	data->argv = NULL;
	data->env_array = NULL;
	data->cwd = NULL;
	data->env = NULL;
	data->sorted_env = NULL;
	data->input = NULL;
	copy_environment(data, envp);
	get_path_ready(data);
}

static void	parse_input(t_data *data, char *input)
{
	data->input = ft_shell_list_split(data, input);
	if (data->input != NULL)
		analyze_input(data);
}

/* static int	init_sigaction(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	sa->sa_flags = SA_NODEFER | SA_SIGINFO;
	sa->sa_handler = SIG_IGN;
	sa->sa_sigaction = &signal_handler;
	return (0);
} */

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	// pid_t	id;
	// struct sigaction	sa;
	// char	*test;

	(void)argv;
	(void)argc;
	// init_sigaction(&sa);
	initialize_data(&data, envp);
	// sigaction(SIGQUIT, &sa, NULL);
	data.cwd = getcwd(NULL, 0);
	while (INFINITY)
	{
		line = readline("Much wow: ");
		if (line == NULL)
			exit_error(&data, "Readline failed");
		if (ft_strncmp(line, "env", 4) == 0)
			env_builtin(&data);
		if (ft_strncmp(line, "export", 6) == 0)
			export_builtin(&data, NULL);
		if (ft_strncmp(line, "unset", 5) == 0)
			unset_builtin(&data, &line[6]);
		if (ft_strncmp(line, "exit", 4) == 0)
			exit_builtin(&data, NULL);
		parse_input(&data, line);
		// id = fork();
		// if (id == 0)
		// 	search_the_path(&data, data.path);
		// wait(NULL);
		add_history(line);
		usleep(1000);
	}
	return (0);
}
