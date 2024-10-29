/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 17:46:34 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 21:17:40 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*buffer;
	size_t	i;
	size_t	s_len;

	i = 0;
	if (s == NULL)
		exit(EXIT_FAILURE);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > (s_len - start))
		len = s_len - start;
	buffer = (char *)malloc(sizeof(char) * (len + 1));
	if (!buffer)
		return (0);
	while (start < s_len && i < len)
		buffer[i++] = s[start++];
	buffer[i] = '\0';
	return (buffer);
}
