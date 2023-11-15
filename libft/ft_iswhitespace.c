/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_iswhitespace.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/10/28 16:09:26 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/11/15 18:14:05 by vincent       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_iswhitespace(int c)
{
	if ((c > 8 && c < 14) || c == 32)
		return (true);
	return (false);
}
