/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexer_chexer.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/19 15:08:20 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/19 15:21:37 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_double_redirection(t_mlist *input)
{
	if (input != NULL && input->pv != NULL)
	{
		if (is_redirection(input->pv->token) == true)
		{
			if (is_redirection(input->token) == true)
			{
				if (input->pv->token == HEREDOC)
					return (false);
				return (true);
			}
		}
	}
	return (false);
}

bool	redirection_ok(t_data *data, t_mlist *input)
{
	if (input->token == COMMAND && ft_strncmp(input->str, "<<", 3) == 0)
	{
		if (input->nx != NULL && is_redirection(input->nx->token) == true)
			lexer_error(data, "error near redirection symbol: ", input->str);
		else
			lexer_error(data, "command not found: ", input->str);
		return (false);
	}
	if (is_redirection(input->token) == true && \
	(is_double_redirection(input->nx) == true || input->nx == NULL))
	{
		lexer_error(data, "error near redirection symbol: ", input->str);
		return (false);
	}
	else if (input->token == FILENAME && input->str[0] == '\0')
	{
		lexer_error(data, "error: ambiguous redirect", NULL);
		return (false);
	}
	return (true);
}
