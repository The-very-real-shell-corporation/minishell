/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   initialize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/27 17:06:10 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/27 18:15:12 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_data(t_data *data, char **envp)
{
	data->exit_status = 0;
	data->input = NULL;
	data->path = NULL;
	data->real_path = NULL;
	data->argv = NULL;
	data->env_array = NULL;
	data->cwd = NULL;
	data->env = NULL;
	data->sorted_env = NULL;
	data->input = NULL;
	copy_environment(data, envp);
	get_path_ready(data);
}

void	parse_input(t_data *data, char *input)
{
	expansion_pack(data, input);
	if (data->input == NULL)
		return ;
	data->argv = list_to_array(data, data->input);
	print_2d_charray(data->argv);
}

int	init_sigaction(struct sigaction *sa)
{
	sigemptyset(&sa->sa_mask);
	// sigaddset(&sa->sa_mask, SIGINT);
	// sigaddset(&sa->sa_mask, SIGQUIT);
	// sigaddset(&sa->sa_mask, SIGTERM);
	sa->sa_flags = SA_NODEFER | SA_SIGINFO;
	sa->sa_handler = SIG_IGN;
	sa->sa_sigaction = &signal_handler;
	return (0);
}