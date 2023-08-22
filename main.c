/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/21 17:02:38 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/08/22 16:16:41 by vvan-der      ########   odam.nl         */
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
		tmp = readline("Very real shell company: ");
		add_history(tmp);
		i++;
		if (i == 5)
		{
			rl_clear_history();
			i = 0;
		}
	}
}
