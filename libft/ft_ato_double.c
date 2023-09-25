/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 18:52:12 by vincent           #+#    #+#             */
/*   Updated: 2023/06/30 10:54:22 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	atod_error(void)
{
	ft_putendl_fd("Error: invalid numerical input", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static int	check_input(const char *str, int i)
{
	if (ft_strlen(str) >= 15)
		atod_error();
	while (ft_iswhitespace(str[i]))
		i++;
	if (str[i] == '-')
		i++;
	while (ft_isdigit(str[i]))
	{
		i++;
		if (str[i] == '.')
		{
			i++;
			break ;
		}
	}
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		atod_error();
	return (i);
}

static void	norm_dodging(double *res, double *c, int i, const char *str)
{
	*res += (str[i] - 48) * (*c);
	*c *= 10.0;
}

long double	ft_ato_double(const char *str)
{
	double	res;
	double	c;
	int		i;

	res = 0;
	c = 1;
	if (str[0] == '-')
		c *= -1;
	i = check_input(str, 0);
	while (i > 0)
	{
		i--;
		if (!ft_isdigit(str[i]) && str[i] != '.')
			return ((long double) res);
		if (str[i] == '.')
		{
			res /= (ft_pow(10, ft_strlen(&str[i]) - 1));
			c /= (ft_pow(10, ft_strlen(&str[i]) - 1));
		}
		else
			norm_dodging(&res, &c, i, str);
	}
	return ((long double) res);
}
