/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lutoa.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/09 16:44:00 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/07/28 12:42:19 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(size_t n, int base)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= base;
		i++;
	}
	return (i);
}

int	ft_lutoa(size_t args, int base, int b)
{
	char	*res;
	int		x;

	x = length(args, base) - 1;
	res = ft_calloc(x + 2, sizeof(char));
	if (!res)
		return (-1);
	while (x >= 0)
	{
		if ((args % base) > 9 && b == 0)
			res[x] = (args % base) + 87;
		else if ((args % base) > 9 && b == 1)
			res[x] = (args % base) + 55;
		else
			res[x] = (args % base) + 48;
		args /= base;
		x--;
	}
	x = ft_putstrlen_fd(res, 1);
	free(res);
	return (x);
}
