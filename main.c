/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/28 21:21:07 by akasiota      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_data *data, char *msg)
{
	clean_up(data);
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;
	pid_t	id;
	// char	*test;

	(void)argv;
	if (argc != 1)
		return (printf("Please insert input after starting minishell"), 1);
	initialize_data(&data, envp);
	data.cwd = getcwd(NULL, 0);
	while (INFINITY)
	{
		set_signals();
		line = readline("Much wow: ");
		// printf("Line: %s\n", line);
		if (line == NULL)
		{
			clean_up(&data);
			return (0);
		}
		parse_input(&data, line);
		if (ft_strncmp(line, "cd", 2) == 0)
			cd_builtin(&data, data.argv[1]);
		if (ft_strncmp(line, "env", 3) == 0)
			env_builtin(&data);
		if (ft_strncmp(line, "export", 6) == 0)
		{
			export_builtin(&data, &line[7]);
		}
		if (ft_strncmp(line, "unset", 5) == 0)
			unset_builtin(&data, &line[6]);
		if (ft_strncmp(line, "exit", 4) == 0)
			exit_builtin(&data, NULL);
		id = fork();
		if (id == 0)
		{
			signals_for_kids();
			search_the_path(&data, data.path);
		}
		else
		{
			unset_signals();
		}
		waitpid(id, &data.exit_status, 0);
		printf("exit status (foist): %d\n", data.exit_status);
		if (WIFSIGNALED(data.exit_status))
		{
			printf("testing please\n");
			if (WTERMSIG(data.exit_status) == SIGINT)
			{
				write(STDOUT_FILENO, "\n", 1);
				data.exit_status = 128 + WTERMSIG(data.exit_status);
			}	
			else if (WTERMSIG(data.exit_status) == SIGQUIT)
			{	
				write(STDOUT_FILENO, "CORE DUMPED MOTHAFUCKA\n", 23);
				data.exit_status = 128 + WTERMSIG(data.exit_status);
			}
			// data.exit_status = WTERMSIG(data.exit_status);
		}
		else
		{
			data.exit_status = WEXITSTATUS(data.exit_status);	
		}
		// data.exit_status = WEXITSTATUS(data.exit_status);
		printf("exit status (twiced): %d\n", data.exit_status);
		add_history(line);
		usleep(1000);
		free(line);
	}
	return (0);
}
