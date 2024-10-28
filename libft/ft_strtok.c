/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:50:14 by xquah             #+#    #+#             */
/*   Updated: 2024/10/28 17:45:43 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*saved_str;
	char		*token;
	int			i;
	int			j;
	int			k;

	if (str != NULL)
		saved_str = str;
	if (saved_str == NULL)
		return (NULL);
	i = 0;
	k = 0;
	while (saved_str[i] != '\0')
	{
		j = 0;
		while (delim[j] != '\0')
		{
			if (saved_str[i] == delim[j])
			{
				saved_str[i] = '\0';
				token = &saved_str[k];
				saved_str = &saved_str[i + 1];
				return (token);
			}
			j++;
		}
		i++;
	}
	token = &saved_str[k];
	saved_str = NULL;
	return (token);
}
