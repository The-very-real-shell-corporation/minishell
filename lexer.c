/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 14:04:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/25 17:53:26 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	analyze_input(t_mlist *input)
{
	tokenize_list(input);
	if (input == NULL)
		printf("%s\n", "error: invalid input");
	else if (1 == 2)
		puts("stuff");
	else
		printf("%s: command not found\n", input->str);
}

static int	assign_token(char *str)
{
	int			token;

	if (ft_strncmp(str, ">>", 3) == 0)
		token = APPEND;
	else if (ft_strncmp(str, "<<", 3) == 0)
		token = HEREDOC;
	else if (ft_strncmp(str, ">", 2) == 0)
		token = RE_OUTPUT;
	else if (ft_strncmp(str, "<", 2) == 0)
		token = RE_INPUT;
	else if (ft_strncmp(str, "|", 2) == 0)
		token = PIPE;
	else if (ft_strncmp(str, "$", 2) == 0)
		token = DOLLAR_SIGN;
	else if (ft_strncmp(str, "\'", 2) == 0)
		token = SINGLE_QUOTE;
	else if (ft_strncmp(str, "\"", 2) == 0)
		token = DOUBLE_QUOTE;
	// else if (command_compare == true)
	// 	token = COMMAND;
	else
		token = WORD;
	return (token);
}

void	tokenize_list(t_mlist *list)
{
	if (list != NULL)
	{
		list->token = COMMAND;
		list = list->nx;
	}
	while (list != NULL)
	{
		list->token = assign_token(list->str);
		list = list->nx;
	}
}
