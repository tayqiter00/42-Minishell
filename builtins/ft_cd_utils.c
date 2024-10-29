/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 20:41:24 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:15:40 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_home(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "HOME=", 5))
			break ;
		envp++;
	}
	if (*envp == NULL)
	{
		ft_dprintf(STDERR_FILENO, "Error: HOME not found\n");
		return (1);
	}
	return (chdir(*envp + 5));
}

char	*update_oldpwd(char *curdir)
{
	char	*updated;

	updated = ft_strjoin("OLDPWD=", curdir);
	if (updated == NULL)
		ft_dprintf(STDERR_FILENO, "malloc failed for update_oldpwd\n");
	return (updated);
}
