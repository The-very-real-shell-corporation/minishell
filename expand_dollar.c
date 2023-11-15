/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_dollar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: vincent <vincent@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/15 16:00:43 by vincent       #+#    #+#                 */
/*   Updated: 2023/11/15 16:02:47 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	switch_bool(bool *quoted)
{
	if (*quoted == true)
		*quoted = false;
	else
		*quoted = true;
}

char	*expand_dollar(t_data *data, char *str)
{
	bool	quoted;
}