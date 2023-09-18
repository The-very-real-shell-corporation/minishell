/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shell_split.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/09/18 14:19:08 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/09/18 14:52:00 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_getamount(char *s)
{
	int	i;
	int	amount;

	i = 0;
	amount = 0;
	while (*s != '\0' && ft_iswhitespace(*s) == true)
		s++;
	if (s[i])
		amount++;
	while (s[i])
	{
		if (ft_iswhitespace(s[i]) == true && \
		ft_iswhitespace(s[i + 1]) == false && s[i + 1])
			amount++;
		i++;
	}
	return (amount);
}

static void	ft_free(char **s2)
{
	int	x;

	x = 0;
	while (s2[x])
	{
		free(s2[x]);
		x++;
	}
	free(s2);
}

static int	ft_special_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_iswhitespace(str[i]) == false)
		i++;
	return (i);
}

static char	**ft_crearray(char **s2, char *s)
{
	int	x;
	int	len;

	x = 0;
	while (*s)
	{
		while (ft_iswhitespace(*s) == true)
			s++;
		if (*s == '\0')
			return (s2);
		len = ft_special_strlen(s);
		s2[x] = ft_calloc(len + 1, sizeof(char));
		if (!s2[x])
			return (ft_free(s2), NULL);
		ft_strlcpy(s2[x], s, len + 1);
		s += len;
		x++;
	}
	return (s2);
}

char	**ft_shell_split(char *s)
{
	char	**out;
	int		amount;

	if (!s)
		return (NULL);
	amount = ft_getamount(s);
	out = malloc((amount + 1) * sizeof(char *));
	if (!out)
		return (NULL);
	if (amount == 0)
		return (*out = NULL, out);
	out = ft_crearray(out, s);
	if (!out)
		return (NULL);
	out[amount] = NULL;
	return (out);
}
