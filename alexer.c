/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 14:04:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/22 17:34:41 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	assign_command_token(t_mlist *node, char *str)
{
	if (ft_strncmp("cd", str, 3) == 0)
		node->token = B_CD;
	else if (ft_strncmp("echo", str, 5) == 0)
		node->token = B_ECHO;
	else if (ft_strncmp("env", str, 4) == 0)
		node->token = B_ENV;
	else if (ft_strncmp("exit", str, 5) == 0)
		node->token = B_EXIT;
	else if (ft_strncmp("export", str, 7) == 0)
		node->token = B_EXPORT;
	else if (ft_strncmp("pwd", str, 4) == 0)
		node->token = B_PWD;
	else if (ft_strncmp("unset", str, 6) == 0)
		node->token = B_UNSET;
	else
		node->token = COMMAND;
}

static t_token	assign_token(char *str)
{
	t_token	token;

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
	else
		token = WORD;
	return (token);
}

static void	tokenize_list(t_data *data) // add redirections and use FILENAME token
{
	t_mlist	*in;

	in = data->input;
	while (in != NULL)
	{
		in->token = assign_token(in->str);
		if (in->pv != NULL && in->pv->token == HEREDOC && in->token == WORD)
			in->token = DOC_DELIM;
		else if (is_redirection(in->token) == true && in->pv != NULL && is_redirection(in->pv->token) == true)
		{
			ft_putendl_fd("error: multiple redirections in a row", STDERR_FILENO);
			clear_mlist(&data->input);
			return ;
		}
		else if ((in->pv == NULL && in->token != HEREDOC) || \
			(in->pv != NULL && in->pv->token == PIPE))
			assign_command_token(in, in->str);
		else if (in->pv != NULL && is_redirection(in->pv->token))
			in->token = FILENAME;
		in = in->nx;
	}
}

void	analyze_input(t_data *data)
{
	if (data->input == NULL)
	{
		printf("%s\n", "error: invalid input");
		return ;
	}
	tokenize_list(data);
}
