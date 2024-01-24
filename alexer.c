/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 14:04:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/24 12:23:12 by vincent       ########   odam.nl         */
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
	else if (ft_strncmp(str, "<<", 3) == 0)
		node->token = HEREDOC;
	else
		node->token = COMMAND;
}

static void	assign_token(t_mlist *node, char *str)
{
	if (ft_strncmp(str, ">>", 3) == 0)
		node->token = APPEND;
	else if (ft_strncmp(str, "<<", 3) == 0)
		node->token = HEREDOC;
	else if (ft_strncmp(str, ">", 2) == 0)
		node->token = RE_OUTPUT;
	else if (ft_strncmp(str, "<", 2) == 0)
		node->token = RE_INPUT;
	else if (ft_strncmp(str, "|", 2) == 0)
		node->token = PIPE;
	else
		node->token = WORD;
}

static void	tokenize_list(t_data *data, t_mlist *in) // add redirections and use FILENAME token
{
	assign_token(in, in->str);
	if (in->pv != NULL && is_redirection(in->pv->token) != NONE \
	&& is_redirection(in->token) != NONE)
		lexer_error(data, "multiple redirections in a row");
	else if (in->pv == NULL || in->pv->token == PIPE)
		assign_command_token(in, in->str);
	if (in != NULL && in->token == HEREDOC)
	{
		if (in->nx == NULL)
			lexer_error(data, "heredoc has no delimiter");
		else
		{
			in->str = ft_strdup2(data, in->nx->str);
			unlink_node(in->nx);
		}
	}
	if (data->input != NULL && in->nx != NULL)
		tokenize_list(data, in->nx);
}

void	analyze_input(t_data *data)
{
	tokenize_list(data, data->input);
	puts("Tokenized list:");
	print_list(data->input);
}
