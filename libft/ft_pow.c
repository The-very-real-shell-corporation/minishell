/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vincent <vincent@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 16:56:15 by vvan-der          #+#    #+#             */
/*   Updated: 2023/06/03 19:38:39 by vincent          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_pow(int number, int power)
{
	long long	x;

	x = (long long) number;
	if (power == 0)
		return (1);
	while (power > 1)
	{
		x *= number;
		power--;
	}
	return (x);
}
