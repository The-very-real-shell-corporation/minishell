/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/17 19:18:08 by vvan-der      ########   odam.nl         */
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
	char	*test;

	(void)argv;
	// (void)envp;
	(void)argc;
	test = ft_calloc(1, 1000);
	initialize_data(&data, envp);
	while (INFINITY)
	{
		line = readline("Much wow: ");
		if (line == NULL)
			exit_error(&data, "Readline failed");
		ft_strcpy(test, "hello");
		if (ft_strncmp(line, "env", 4) == 0)
			env_builtin(&data);
		if (ft_strncmp(line, "export", 7) == 0)
			export_builtin(&data, test);
		add_history(line);
		parse_input(&data, line);
		usleep(1000);
	}
	return (0);
}
