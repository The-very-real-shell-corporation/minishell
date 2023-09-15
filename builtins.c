/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/14 19:46:29 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/15 17:31:41 by vvan-der      ########   odam.nl         */
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

	out = getcwd(NULL, 0);
	printf("%s\n", out);
	free(out);
}

void	cd_builtin(char *path)
{
	if (chdir(path) == -1)
		printf("Error: \"%s\" is not a directory\n", path);
}

void	env_builtin(char **envp)
{
	while (*envp != NULL)
	{
		printf("%s\n", *envp);
		envp++;
	}
}

void	exit_builtin(char *msg)
{
	if (msg == NULL)
		exit(0);
}
