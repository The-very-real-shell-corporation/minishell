/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/14 20:36:40 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*tmp;
	// int		i;

	argc = 0;
	argv = NULL;
	// i = 0;
	while (true)
	{
		tmp = readline("NULL: ");
		add_history(tmp);
		if (ft_strncmp(tmp, "pwd", 3) == 0)
			pwd_builtin();
		else if (ft_strncmp(tmp, "echo -n", 7) == 0)
			echo_builtin(tmp + 8, "-n");
		else if (ft_strncmp(tmp, "echo", 4) == 0)
			echo_builtin(tmp + 5, NULL);
		usleep(1000);
		// i++;
		// printf("%d\n", rl_on_new_line());
		// if (i == 4)
		// {
		// 	rl_replace_line("TEAL COMPANY I SWEAT\n", 10);
		// 	rl_redisplay();
		// 	i = 0;
		// 	break ;
		// }
	}
	free(tmp);
	return (0);
}
