/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:28:42 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:59:02 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_dprinthex(int fd, unsigned long n, const char *base)
{
	int	count;

	count = 0;
	if (n > 15)
		count += ft_dprinthex(fd, n / 16, base);
	count += ft_dputchar(*(base + (n % 16)), fd);
	return (count);
}

int	ft_dputptr(int fd, void *format)
{
	unsigned long	n;
	const char		*base;
	int				count;

	n = (unsigned long)format;
	base = "0123456789abcdef";
	count = ft_dputstr(fd, "0x");
	count += ft_dprinthex(fd, n, base);
	return (count);
}
