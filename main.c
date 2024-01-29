/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/29 20:53:24 by vvan-der      ########   odam.nl         */
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
	while (INFINITY)
	{
		set_signals();
		get_input_and_parse(&data);
		carry_out_orders(&data, data.pipelines);
		loop_clean(&data);
		unlink(HD_PATH);
	}
	return (0);
}
