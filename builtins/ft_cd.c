/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 16:48:20 by qtay              #+#    #+#             */
/*   Updated: 2024/10/24 12:13:51 by qtay             ###   ########.fr       */
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

int	cd_to_dir(t_tokennode *args, char **envp)
{
    if (!args || args->is_meta_char)
        return (cd_home(envp));
    else if (args->next == NULL)
        return (chdir(args->token));
    else
    {
        dprintf(STDERR_FILENO, "cd: too many arguments\n");
        return (1);
    }
}

int handle_cd_error(int errno, t_tokennode *args)
{
    if (errno == -1)
    {
        dprintf(STDERR_FILENO, "cd: %s: No such file or directory\n", args->token);
        return (1);
    }
    else if (errno)
    {
        dprintf(STDERR_FILENO, "cd: %s: Permission denied\n", args->token);
        return (1);
    }
    return (0);
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
    int		errno;
    char	*curdir;

    errno = 0;
    curdir = getenv("PWD");
    if (curdir == NULL)
    {
        dprintf(STDERR_FILENO, "Error: PWD environment variable not found\n");
        return (1);
    }
    errno = cd_to_dir(args, envp);
    if (handle_cd_error(errno, args))
        return (1);
    change_oldpwd(curdir, envp);
    change_pwd(envp);
    return (0);
}
