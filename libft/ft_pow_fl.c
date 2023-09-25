/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow_fl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvan-der <vvan-der@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 16:14:16 by vvan-der          #+#    #+#             */
/*   Updated: 2023/06/30 10:56:19 by vvan-der         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_pow_fl(long double number, int power)
{
	long double	x;

	x = number;
	if (power == 0)
		return (1);
	while (power > 1)
	{
		x *= number;
		power--;
	}
	return (x);
}
