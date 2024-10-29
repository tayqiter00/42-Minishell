/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_u_putnbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:28:18 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 21:55:57 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_d_u_putnbr(int fd, unsigned int n)
{
	int	count;

	count = ft_dputnbr(fd, n);
	return (count);
}
/*
int	main()
{
	printf("[%d]\n", ft_putnbr(-2147483648, 1));
	printf("[%d]\n", ft_u_putnbr(-2147483648, 1));
	return (0);
}*/
