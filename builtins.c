/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 19:46:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/14 20:38:08 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(char *msg, char *flag)
{
	if (flag == NULL)
		printf("%s\n", msg);
	else if (ft_strncmp(flag, "-n", 2) == 0)
		printf("%s%%", msg);
}

void	pwd_builtin(void)
{
	char	*out;

	out = getcwd(NULL, 1000);
	printf("%s\n", out);
	free(out);
}

void	exit_builtin(char *msg)
{
	if (msg == NULL)
		exit(0);
	
}