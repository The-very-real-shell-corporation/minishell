/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iswhitespace.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 16:09:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2024/02/06 15:06:47 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhitespace(int c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (true);
	return (false);
}
