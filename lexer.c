/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 14:04:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/19 15:38:57 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	analyze_input(char **input)
{
	// if (is_command(*input) == true)
	if (1 == 2)
		puts("stuff");
	else
		printf("%s: command not found\n", input[0]);
}

int	assign_token(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		
	}
}
