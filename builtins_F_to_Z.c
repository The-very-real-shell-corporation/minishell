/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_F_to_Z.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/16 16:35:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/23 15:39:24 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_data *data)
{
	char	*out;

	out = getcwd(NULL, 0);
	if (out != NULL)
	{
		printf("%s\n", out);
		free(out);
	}
	else
		exit_error(data, "Pwd determining failed\n");
}

void	unset_builtin(t_data *data, char *input)
{
	t_mlist *tmp;
	
	if (input == NULL)
	{
		printf("Please provide a variable to unset\n");
		return ;
	}
	tmp = find_input(data->env, input);
	if (tmp != NULL)
		unlink_node(tmp);
}