/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/19 18:43:15 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
	{
		ft_putendl_fd("Insert input after starting minishell", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	ft_putendl_fd("Welcome to The Bashbasher!", STDOUT_FILENO);
	ft_putendl_fd("Please write \"about\" for more information", STDOUT_FILENO);
	initialize_data(&data, envp);
	while (INFINITY)
	{
		set_signals(&data);
		if (get_input_and_parse(&data) == true)
			carry_out_orders(&data, data.pipelines, 0);
		loop_clean(&data);
		unlink(HD_PATH);
	}
}
