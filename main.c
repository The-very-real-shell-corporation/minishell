/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/16 20:11:50 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_error(t_data *data, char *msg)
{
	(void)data;
	// clean_up();
	ft_putstr_fd(msg, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	initialize_data(t_data *data, char **envp)
{
	data->input = NULL;
	data->path = NULL;
	copy_environment(data, envp);
	sort_environment(data);
	get_path_ready(data);
}

static void	parse_input(t_data *data, char *input)
{
	data->input = ft_shell_list_split(data, input);
	if (data->input != NULL)
		analyze_input(data, data->input);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_data	data;

	(void)argv;
	// (void)envp;
	(void)argc;
	initialize_data(&data, envp);
	while (INFINITY)
	{
		line = readline("Much wow: ");
		if (line == NULL)
			exit_error(&data, "Readline failed");
		if (ft_strncmp(line, "env", 4) == 0)
			env_builtin(&data);
		add_history(line);
		parse_input(&data, line);
		if (data.input != NULL)
		{
			print_list(data.input);
			clear_mlist(&data.input);
		}
		usleep(1000);
	}
	return (0);
}
