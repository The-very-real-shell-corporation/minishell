/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 15:36:58 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_data *data, char *msg)
{
	clean_up(data);
	ft_putstr_fd(msg, STDERR_FILENO);
	write(STDERR_FILENO, "\n", 1);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (printf("Please insert input AFTER starting minishell"), 1);
	initialize_data(&data, envp);
	while (INFINITY)
	{
		data.cwd = getcwd(NULL, 0);
		if (data.cwd == NULL)
			exit_error(&data, "cwd failed");
		set_signals();
		data.line = readline("WE SHELL SEE: ");
		if (data.line == NULL)
		{
			clean_up(&data);
			printf("exit\n");
			return (0);
		}
		parse_input(&data, data.line);
		if (data.input != NULL)
		{
			execute(&data, data.pipelines, data.pids);
			add_history(data.line);
		}
		loop_clean(&data);
	}
	return (0);
}
