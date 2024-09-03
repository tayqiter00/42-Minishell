/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 17:43:01 by qtay              #+#    #+#             */
/*   Updated: 2024/03/05 12:29:49 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	int				total_len;
	char			*buffer;

	i = 0;
	if (!s)
		return (NULL);
	total_len = ft_strlen(s);
	buffer = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!buffer)
		return (0);
	while (s[i])
	{
		buffer[i] = (*f)(i, s[i]);
		i++;
	}
	buffer[i] = '\0';
	return (buffer);
}
