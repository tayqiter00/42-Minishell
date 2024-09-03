/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:27:31 by qtay              #+#    #+#             */
/*   Updated: 2024/03/05 12:41:45 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
/*
void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*buffer;
	size_t			i;

	if (count > 0 && size > INT_MAX / count)
		return (0);
	i = 0;
	buffer = (unsigned char *)malloc(size * count);
	if (!buffer)
		return (0);
	while (i < size * count)
		buffer[i++] = 0;
	return ((void *)buffer);
}
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count > 0 && size > INT_MAX / count)
		return (NULL);
	ptr = malloc(count * size);
	if (ptr == NULL)
		return (ptr);
	ft_bzero(ptr, size * count);
	return (ptr);
}
