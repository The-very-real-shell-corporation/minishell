/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   alexer.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 14:04:47 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/19 15:27:22 by vvan-der      ########   odam.nl         */
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
	else if (node->pv != NULL && is_redirection(node->pv->token) == true)
	{
		if (node->pv->token != PIPE && node->pv->token != HEREDOC)
			node->token = FILENAME;
	}
	else
		node->token = WORD;
}

static void	check_list(t_data *data, t_mlist *input)
{
	while (input != NULL)
	{
		if (redirection_ok(data, input) == false)
			return ;
		if (input->token == HEREDOC)
		{
			input->args = ft_split(input->nx->str, '\0');
			if (input->args == NULL)
				exit_error(data, "split alloc failed");
			unlink_node(input->nx);
		}
		input = input->nx;
	}
}

void	tokenize_list(t_data *data, t_mlist *in)
{
	while (in != NULL)
	{
		assign_token(in, in->str);
		if (in->pv == NULL || (in->pv->token == PIPE && in->token != PIPE))
			assign_command_token(in, in->str);
		in = in->nx;
	}
	check_list(data, data->input);
}
