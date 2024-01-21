/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/21 19:15:04 by vincent       ########   odam.nl         */
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

static void	carry_out_orders(t_data *data, t_mlist **pipelines)
{
	int	i;

	i = 0;
	while (pipelines[i] != NULL)
	{
		execute(data, pipelines[i], data->pids);
	}
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
		set_signals();
		get_input_and_parse(&data);
		carry_out_orders(&data, data.pipelines);
		loop_clean(&data);
	}
	return (0);
}
