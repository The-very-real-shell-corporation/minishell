/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/04 13:59:36 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv)
{
	char	*tmp;
	int		i;

	argc = 0;
	argv = NULL;
	i = 0;
	while (i < 5)
	{
		tmp = readline("NULL: ");
		add_history(tmp);
		i++;
		printf("%d\n", rl_on_new_line());
		if (i == 4)
		{
			rl_replace_line("TEAL COMPANY I SWEAT\n", 10);
			rl_redisplay();
			i = 0;
		}
	}
}
