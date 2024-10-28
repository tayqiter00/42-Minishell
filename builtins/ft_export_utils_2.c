/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:08:35 by xquah             #+#    #+#             */
/*   Updated: 2024/10/28 17:34:49 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	entry_has_valid_name(char *args)
{
	if (is_special_env_name(*args))
		return (false);
	else
	{
		while (is_valid_env_name(*args))
			args++;
		return (true);
	}
	return (false);
}

/**
 * Check if the variable already exist in the envp
 */
bool	is_not_duplicate(char **envp, char *args)
{
	int	args_name_len;

	while (*envp)
	{
		args_name_len = ft_strcspn(args, "=");
		if (!ft_strncmp(*envp, args, args_name_len))
			return (false);
		envp++;
	}
	return (true);
}
