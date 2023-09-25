/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: vvan-der <vvan-der@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/12/06 16:22:41 by vvan-der      #+#    #+#                 */
/*   Updated: 2023/07/28 12:43:18 by vvan-der      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptr(void *arg)
{
	int	x;

	x = write(1, "0x", 2);
	if (x == -1)
		return (x);
	x = ft_lutoa((size_t) arg, 16, 0);
	if (x == -1)
		return (-1);
	return (x + 2);
}

static int	ft_handle(const char *input, va_list args)
{
	if (*input == 'c')
		return (ft_putchar_fd(va_arg(args, int), 1));
	else if (*input == 's')
		return (ft_putstrlen_fd(va_arg(args, char *), 1));
	else if (*input == 'p')
		return (ft_ptr(va_arg(args, void *)));
	else if (*input == 'd' || *input == 'i')
		return (ft_writoa(va_arg(args, int)));
	else if (*input == 'u')
		return (ft_lutoa(va_arg(args, unsigned int), 10, 0));
	else if (*input == 'x')
		return (ft_lutoa(va_arg(args, unsigned int), 16, 0));
	else if (*input == 'X')
		return (ft_lutoa(va_arg(args, unsigned int), 16, 1));
	else if (*input == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

static int	ft_gobrr(const char *input, va_list args, int i, int count)
{
	int	write_ret;

	while (input[i])
	{
		write_ret = 0;
		if (input[i] == '%' && (input [i + 1]))
		{
			i++;
			if (ft_strchr("cspdiuxX%", input[i]))
			{
				write_ret = ft_handle(&input[i], args);
				if (write_ret == -1)
					return (-1);
			}
		}
		else if (input[i] != '%')
		{
			write_ret = ft_putchar_fd(input[i], 1);
			if (write_ret == -1)
				return (-1);
		}
		count += write_ret;
		i++;
	}
	return (count);
}

int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		i;
	int		count;

	i = 0;
	count = 0;
	va_start(args, input);
	count = ft_gobrr(input, args, i, count);
	va_end(args);
	return (count);
}
