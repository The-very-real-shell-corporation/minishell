/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 14:04:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 13:44:27 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	analyze_input(t_mlist *input)
{
	// if (is_command(*input) == true)
	if (input == NULL)
		printf("%s\n", "error: invalid input");
	else if (1 == 2)
		puts("stuff");
	else
		printf("%s: command not found\n", input->str);
}

/* int	assign_token(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		
	}
} */
