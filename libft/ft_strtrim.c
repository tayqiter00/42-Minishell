/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 15:11:52 by qtay              #+#    #+#             */
/*   Updated: 2024/03/01 17:15:32 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static	int	start(char const *s1, char const *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j])
	{
		while (s1[i] == set[j] && s1[i])
		{
			i++;
			j = 0;
		}
		j++;
	}
	return (i);
}

static int	end(char const *s1, char const *set)
{
	int	len;
	int	j;

	j = 0;
	len = ft_strlen(s1);
	while (set[j])
	{
		while (s1[len - 1] == set[j] && len > 1)
		{
			len--;
			j = 0;
		}
		j++;
	}
	return (len - 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start_addr;
	int		end_addr;
	int		total_len;
	char	*buffer;

	i = 0;
	if (!s1 || !set)
		return (ft_strdup(""));
	start_addr = start(s1, set);
	end_addr = end(s1, set);
	if (end_addr < start_addr)
		return (ft_strdup(""));
	total_len = (end_addr - start_addr + 1);
	buffer = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!buffer)
		return (0);
	while (i < total_len && start_addr <= end_addr)
	{
		buffer[i] = s1[start_addr];
		i++;
		start_addr++;
	}
	buffer[i] = '\0';
	return (buffer);
}
/*
int	main()
{
	char	*str = "          ";
	char	*set = " ";

	printf("%s\n",ft_strtrim(str, set));
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[start]) && start <= end)
		start++;
	if (start > end)
		return (ft_strdup(s1 + end + 1));
	while (ft_strchr(set, s1[end]) && end >= 0)
		end--;
	str = malloc(end - start + 2);
	if (!str)
		return (NULL);
	ft_strlcpy(str, &s1[start], end - start + 2);
	return (str);
}*/
