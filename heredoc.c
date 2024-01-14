/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/12/21 14:48:23 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/14 17:22:18 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_heredoc(t_mlist *input, t_mlist *heredoc)
{
	t_mlist	*tmp;

	while (go_to_token(&input, HEREDOC) == true)
	{
		tmp = input;
		if (go_to_token(&input, HEREDOC) == true)
		{
			input = tmp->nx->nx;
			unlink_node(tmp->nx);
			unlink_node(tmp);
		}
	}
	if (input == NULL)
		return (heredoc);
	else
	{
		while (heredoc != NULL)
		{
			insert_node(input->pv, input, heredoc);
			heredoc = heredoc->nx;
		}
	}
}

static char	**fetch_delims(t_data *data, t_mlist *input)
{
	t_mlist	*delims;

	while (input != NULL && go_to_token(&input, HEREDOC) == true)
	{
		if (input->nx != NULL)
			node_addback(&delims, new_node(data, input->nx->str, NULL, INITIALIZED));
		input = input->nx;
	}
	return (list_to_array(data, delims, DUMMY));
}

/*	It seems bash ignores the output of all heredocs until the final one, 
	so I just don't add any nodes until at the last delimiter	*/

int	doodle_in_doc(t_data *data, t_mlist *doc, char **delim)
{
	bool	expansion;
	int		i;

	expansion = true;
	i = 0;
	while (delim[i] != NULL)
	{
		free(data->line);
		if (first_last(delim[i], '\"') == true || first_last(delim[i], '\'') == true)
			expansion = false;
		data->line = readline("> ");
		if (data->line == NULL)
			return (1);
		if (expansion == true)
			expand_dollar(data, &data->line);
		if (delim[i + 1] == NULL)
			node_addback(&doc, new_node(data, data->line, NULL, INITIALIZED));
		if (ft_strncmp(data->line, delim[i], ft_strlen(delim[i])) == 0)
			i++;
	}
	return (0);
}

/*	Removes all nodes from input with "<<" and the delimiter, inserting the user's input	

To do: implement signals so interrupting heredoc doesn't close minishell and make sure
ctrl + D works (EOF)	*/

void	whatsup_doc(t_data *data, t_mlist *input)
{
	data->delim = fetch_delims(data, input);
	doodle_in_doc(data, data->heredoc, data->delim);
	insert_heredoc(&(node_first(data->input)), data->heredoc);
}