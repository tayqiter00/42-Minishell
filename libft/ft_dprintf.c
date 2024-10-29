/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 15:54:32 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:58:06 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_specifier(char c)
{
	return (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%');
}

static int	print_format(int fd, char specifier, va_list ap)
{
	int		count;

	count = 0;
	if (specifier == 'c')
		count += ft_dputchar(va_arg(ap, int), fd);
	else if (specifier == 's')
		count += ft_dputstr(fd, va_arg(ap, char *));
	else if (specifier == 'p')
		count += ft_dputptr(fd, va_arg(ap, void *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_dputnbr(fd, va_arg(ap, int));
	else if (specifier == 'u')
		count += ft_d_u_putnbr(fd, va_arg(ap, unsigned int));
	else if (specifier == 'x' || specifier == 'X')
		count += ft_dputhex(fd, va_arg(ap, unsigned int), specifier);
	else if (specifier == '%')
		count += ft_dputchar('%', fd);
	else
		return (-1);
	return (count);
}

int	ft_dprintf(int fd, const char *format, ...)
{
	int		count;
	va_list	ap;

	va_start(ap, format);
	count = 0;
	while (*format)
	{
		if (*format == '%' && check_specifier(*(format + 1)))
			count += print_format(fd, *(++format), ap);
		else
			count += write(fd, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}
