/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 15:44:45 by xquah             #+#    #+#             */
/*   Updated: 2024/10/02 17:01:23 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*realloc_entry(char *entry)
{
	char	*temp;

	temp = malloc(ft_strlen(entry) + 1);
	ft_strlcpy(temp, entry, ft_strlen(entry));
	free(entry);
	return temp;
}

static char *unset_entry(char *entry, t_tokennode *args)
{
	int			env_name_len;
	t_tokennode	*current_arg;

	if (ft_strchr(args->token, '=') != NULL)
		return (entry);
	env_name_len = ft_strcspn(entry, "=");
	current_arg = args;
	while (current_arg)
	{
		if (is_special_env_name(*entry))
			return (entry);
		if (!ft_strncmp(entry, args->token, env_name_len))
		{
			entry = realloc_entry(entry);
			if (!entry)
			{
				printf("ft_realloc failed for entry\n");
				exit(-1);
			}
			*entry = '\0';
			return (entry);
		}
		current_arg = current_arg->next;
	}
	return (entry);
}

int ft_unset(char **envp, t_tokennode *args)
{
	if (args == NULL)
		return (0);
	while (*envp)
	{
		*envp = unset_entry(*envp, args);
		envp++;
	}
	return (0);
}