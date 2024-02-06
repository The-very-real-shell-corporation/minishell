/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/06 15:07:56 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	if (argc != 1)
		return (printf("Please insert input AFTER starting minishell"), 1);
	initialize_data(&data, envp);
	printf("Welcome to The Bashbasher!\n");
	printf("Please write \"about\" for more information\n");
	while (INFINITY)
	{
		set_signals();
		if (get_input_and_parse(&data) == true)
			carry_out_orders(&data, data.pipelines, 0);
		loop_clean(&data);
		unlink(HD_PATH);
	}
	return (0);
}
