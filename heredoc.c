/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/16 18:48:45 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mlist	*doodle_in_doc(t_data *data, t_mlist *doc, t_mlist *tmp, char *delim)
{
	bool	expansion;

	expansion = true;
	if (first_last(delim, '\"') == true || first_last(delim, '\'') == true)
		expansion = false;
	while (INFINITY)
	{
		free(data->line);
		data->line = readline("> ");
		if (data->line == NULL || \
		ft_strncmp(data->line, delim, ft_strlen(delim)) == 0)
			break ;
		if (expansion == true)
			expand_dollar(data, &data->line);
		node_addback(&doc, \
		new_node(data, ft_strdup2(data, data->line), NULL, INITIALIZED));
	}
	if (doc != NULL)
		tmp = new_node(data, NULL, list_to_array(data, doc, DUMMY), DOC_INPUT);
	clear_mlist(&doc);
	return (tmp);
}

/*	To do: implement signals so interrupting heredoc doesn't close minishell and make sure
ctrl + D works (EOF)	*/

t_mlist	*whatsup_doc(t_data *data, t_mlist *input)
{
	if (input->nx == NULL || input->nx->token != DOC_DELIM)
	{
		write(STDERR_FILENO, "Could not find heredoc delimiter\n", 34);
		return (NULL);
	}
	return (doodle_in_doc(data, NULL, NULL, input->nx->str));
}
