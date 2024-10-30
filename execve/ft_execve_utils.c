/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:34:52 by xquah             #+#    #+#             */
/*   Updated: 2024/10/30 10:54:15 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmdlist(t_tokenlist *currcmd)
{
	t_tokennode	*current;
	int			count;

	count = 0;
	current = currcmd->head;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}

char	*strjoin_sep(char const *s1, char const *s2, char *sep)
{
	char	*buffer;
	int		total_len;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(sep);
	buffer = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!buffer)
		exit(3);
	ft_strlcpy(buffer, s1, total_len + 1);
	ft_strlcat(buffer, sep, total_len + 1);
	ft_strlcat(buffer, s2, total_len + 1);
	return (buffer);
}

void	construct_path(char *bin, char *path, char **full_path)
{
	if (bin[0] == '.' || bin[0] == '/')
		*full_path = strjoin_sep(bin, "", "");
	else
		*full_path = strjoin_sep(path, bin, "/");
}
