/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:48:20 by qtay              #+#    #+#             */
/*   Updated: 2024/09/02 20:15:43 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <linux/limits.h>

int	cd_home(char **envp)
{
	while (*envp)
	{
		if (!strncmp(*envp, "HOME=", 5)) // ft
			break ;
		*envp++;
	}
	return (chdir(*envp + 5));
}

char	*update_oldpwd(char *curdir)
{
	char	*updated;

	updated = ft_strjoin("OLDPWD=", curdir);
	if (updated == NULL)
		dprintf(STDERR_FILENO, "malloc failed for update_oldpwd\n"); // ft
	return (updated);
}

void	change_oldpwd(char *curdir, char **envp)
{
	while (*envp)
	{
		if (!strncmp(*envp, "OLDPWD=", 7)) // ft
		{
			free(*envp);
			*envp = update_oldpwd(curdir);
			break ;
		}
		*envp++;
	}
}

void	change_pwd(char **envp)
{
	char	s[PATH_MAX];

	while (*envp)
	{
		if (!strncmp(*envp, "PWD=", 4)) // ft
		{
			free(*envp);
			*envp = getcwd(s, PATH_MAX - 1);
			break ;
		}
		*envp++;
	}
}

/**
 * Not handling cd ~ currently
 * 
 * cd seems to be working but not sure if OLDPWD and PWD are changed - need to check
 * 
 * Check that it works for relative and absolute path
 */
int	ft_cd(t_tokennode *args, char **envp)
{
	int	errno;
	char	*curdir;

	errno = 0;
	curdir = getenv("PWD");
	if (!args || args->is_meta_char)
		errno = cd_home(envp);
	else if (args->next == NULL)
		errno = chdir(args->token);
	else
	{
		dprintf(STDERR_FILENO, "cd: too many arguments\n"); // ft_dprintf
		return (1); // return error
	}
	// if (errno)
	// {
	// 	if (errno == -1)
	// 	{
	// 		dprintf(STDERR_FILENO, "cd: %s: No such file or directory\n",
	// 			args->token); // ft_dprintf (can simplify if too long)
	// 			return (1); // think about return value
	// 	}
	// 	else
	// 	{
	// 		dprintf(STDERR_FILENO, "cd: %s: Permission denied\n", args->token); // ft_dprintf
	// 		return (1); // think about return value
	// 	}
	// }
	change_oldpwd(curdir, envp);
	change_pwd(envp);
}
