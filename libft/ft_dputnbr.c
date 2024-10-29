/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputnbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:28:02 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:58:53 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dputnbr(int fd, long n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		ft_dputchar('-', fd);
		count++;
		n = -n;
	}
	if (n > 9)
		count += ft_dputnbr(fd, n / 10);
	count += ft_dputchar(n % 10 + '0', fd);
	return (count);
}
/*
int	main()
{
	printf("[%d]\n", ft_putnbr(2147483647));
	return (0);
}*/
