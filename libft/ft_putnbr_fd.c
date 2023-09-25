/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:29:13 by vvan-der          #+#    #+#             */
/*   Updated: 2023/03/10 15:43:39 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int x)
{
	int	i;

	i = 0;
	if (x <= 0)
		i++;
	while (x != 0)
	{
		x /= 10;
		i++;
	}
	return (i);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	str[12];
	int		i;
	long	x;

	i = length(n);
	str[i] = '\0';
	x = (long) n;
	if (x < 0)
	{
		str[0] = '-';
		x *= -1;
	}
	i--;
	while (x > 9 && i > 0)
	{
		str[i] = (x % 10) + 48;
		x /= 10;
		i--;
	}
	str[i] = x + 48;
	ft_putstr_fd(str, fd);
}
