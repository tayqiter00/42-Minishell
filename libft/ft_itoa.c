/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 18:26:31 by qtay              #+#    #+#             */
/*   Updated: 2024/09/04 15:09:03 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	int_len(int n)
{
	size_t	count;

	count = 1;
	n /= 10;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t	len;
	long	nbr;
	char	*buffer;

	nbr = n;
	len = int_len(n);
	if (n < 0)
	{
		nbr *= -1;
		len++;
	}
	buffer = (char *)malloc(sizeof(char) * (len + 1));
	if (!buffer)
		exit(3);
	buffer[len] = '\0';
	while (len--)
	{
		buffer[len] = nbr % 10 + 48;
		nbr /= 10;
	}
	if (n < 0)
		buffer[0] = '-';
	return (buffer);
}
/*
#include <stdio.h>

int	main()
{
	int	test_numbers[] = {123, -456, 7890, -12345, 0};
	for (size_t i = 0; i < 5; ++i) 
	{
        printf("Integer: %d, String: %s\n", test_numbers[i], 
		ft_itoa(test_numbers[i]));
    }
    return 0;
}*/
