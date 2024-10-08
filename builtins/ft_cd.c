/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:48:20 by qtay              #+#    #+#             */
/*   Updated: 2024/10/05 03:47:30 by qtay             ###   ########.fr       */
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
	if (*envp == NULL)
	{
		dprintf(STDERR_FILENO, "Error: HOME not found\n");
		return (1);
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

/**
 * If doesnt exist, add it
 */
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
	char	*cwd;

	while (*envp)
	{
		if (!ft_strncmp(*envp, "PWD=", 4)) // ft
		{
			cwd = getcwd(s, PATH_MAX - 1);
			if (!cwd)
			{
				dprintf(STDERR_FILENO, "getcwd failed\n");
				return ;
			}
			free(*envp);
			*envp = ft_strdup(cwd);
			if (!*envp)
   				dprintf(STDERR_FILENO, "ft_strdup failed\n");
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
 * Check that it works for relative and absolute path.
 * 
 * Note: the commented part is just error checking; can optionally be removed
 */
int	ft_cd(t_tokennode *args, char **envp)
{
	int	errno;
	char	*curdir;

	errno = 0;
	curdir = getenv("PWD");
	if (curdir == NULL) // leave it first
	{
		dprintf(STDERR_FILENO, "Error: PWD environment variable not found\n");
		return (1);
	}
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
