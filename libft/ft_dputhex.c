/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputhex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:27:44 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:58:39 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dputhex(int fd, unsigned int n, char specifier)
{
	int		count;
	char	*base;

	count = 0;
	if (specifier == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (n > 15)
		count += ft_dputhex(fd, n / 16, specifier);
	count += ft_dputchar(*(base + (n % 16)), fd);
	return (count);
}

/*
int	main()
{
	printf("[%d]\n", ft_puthex(1234, 'X'));
	return (0);
}*/
