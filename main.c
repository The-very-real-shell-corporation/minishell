/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/12/05 18:42:16 by vvan-der      ########   odam.nl         */
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
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (printf("Please insert input after starting minishell"), 1);
	initialize_data(&data, envp);
	while (INFINITY)
	{
		data.cwd = getcwd(NULL, 0);
		if (data.cwd == NULL)
			exit_error(&data, "cwd failed");
		set_signals();
		data.line = readline("Much wow: ");
		if (data.line == NULL)
		{
			clean_up(&data);
			return (0);
		}
		parse_input(&data, data.line);
		execute(&data);
		add_history(data.line);
		loop_clean(&data);
	}
	return (0);
}
