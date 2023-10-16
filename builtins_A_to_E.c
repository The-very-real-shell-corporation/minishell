/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins_A_to_E.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 19:46:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/10/16 20:06:37 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_builtin(char *path)
{
	if (chdir(path) == -1)
		printf("Error: \"%s\" is not a directory\n", path);
}

void	echo_builtin(char *msg, char *flag)
{
	if (flag == NULL)
		printf("%s\n", msg);
	else if (ft_strncmp(flag, "-n", 2) == 0)
		printf("%s%%", msg);
}

void	env_builtin(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i] != NULL)
	{
		printf("%s\n", data->env[i]);
		i++;
	}
	// while (data->sorted_env != NULL)
	// {
	// 	printf("%s\n", data->sorted_env->str);
	// 	data->sorted_env = data->sorted_env->nx;
	// }
}

void	exit_builtin(char *msg)
{
	if (msg == NULL)
		exit(0);
}
/* 
void	export_builtin(t_data *data, char *input)
{
	if (input == NULL)
		
	else
	
} */

