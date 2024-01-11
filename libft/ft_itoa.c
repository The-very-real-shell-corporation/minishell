/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/31 17:06:09 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/01/11 15:21:09 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	res[12];
	int		i;
	long	j;

	ft_memset(res, 'a', 12);
	res[11] = '\0';
	i = 10;
	j = (long) n;
	if (n < 0)
		j *= -1;
	while (j > 9)
	{
		res[i] = (j % 10) + 48;
		j /= 10;
		i--;
	}
	res[i] = j + 48;
	if (n < 0)
		res[i - 1] = '-';
	return (ft_strtrim(res, "a"));
}

char	*ft_itoa2(t_data *data, int n)
{
	char	res[12];
	int		i;
	long	j;

	ft_memset(res, 'a', 12);
	res[11] = '\0';
	i = 10;
	j = (long) n;
	if (n < 0)
		j *= -1;
	while (j > 9)
	{
		res[i] = (j % 10) + 48;
		j /= 10;
		i--;
	}
	res[i] = j + 48;
	if (n < 0)
		res[i - 1] = '-';
	return (ft_strtrim2(data, res, "a"));
}
