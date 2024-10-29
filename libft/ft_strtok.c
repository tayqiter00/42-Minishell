/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtok.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:50:14 by xquah             #+#    #+#             */
/*   Updated: 2024/10/29 11:28:08 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtok(char *str, const char *delim)
{
	static char	*last = NULL;
	char		*token_start;

	if (str != NULL)
		last = str;
	if (last == NULL)
		return (NULL);
	while (*last && ft_strchr(delim, *last))
		last++;
	if (*last == '\0')
	{
		last = NULL;
		return (NULL);
	}
	token_start = last;
	while (*last && !ft_strchr(delim, *last))
		last++;
	if (*last)
	{
		*last = '\0';
		last++;
	}
	else
		last = NULL;
	return (token_start);
}

// #include <stdio.h>
// #include <string.h>

// int	main()
// {
// 	char str1[] = "red.blue-green";
// 	char str2[] = "red.blue-green";
// 	char *delim = ".-";
// 	char *token = ft_strtok(str1, delim);
// 	char *token2 = strtok(str2, delim);

// while (token) {
//     printf("ft_strtok   : %s\n", token);
//     token = ft_strtok(NULL, delim);
// }
// printf("\n");
// while (token2) {
//     printf("strtok      : %s\n", token2);
//     token2 = strtok(NULL, delim);
// }
// }
