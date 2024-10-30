/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:00:46 by xquah             #+#    #+#             */
/*   Updated: 2024/10/30 10:48:14 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_executable(char *full_path)
{
	DIR	*dp;

	dp = opendir(full_path);
	if (dp != NULL)
	{
		closedir(dp);
		return (false);
	}
	return (true);
}

static char	**currcmd_to_2d_array(t_tokenlist *currcmd)
{
	char		**result;
	t_tokennode	*current;
	int			i;

	result = malloc(sizeof(char *) * (count_cmdlist(currcmd) + 1));
	if (result == NULL)
	{
		ft_dprintf(STDERR_FILENO, "malloc failed for result\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	current = currcmd->head;
	while (current)
	{
		result[i] = ft_strdup(current->token);
		if (result[i] == NULL)
		{
			ft_dprintf(STDERR_FILENO, "ft_strdup failed for result[%d]\n", i);
			exit(EXIT_FAILURE);
		}
		i++;
		current = current->next;
	}
	result[i] = NULL;
	return (result);
}

static char	*find_full_bin_path(char *bin, char **envp)
{
	int		i;
	char	*path;
	char	*full_path;

	if (is_invalid_filename(bin))
		return (NULL);
	else if (is_executable(bin) && access(bin, X_OK) == 0)
		return (bin);
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) != 0)
			continue ;
		path = ft_strtok(envp[i] + 5, ":");
		while (path)
		{
			construct_path(bin, path, &full_path);
			if (is_executable(full_path) && access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			path = ft_strtok(NULL, ":");
		}
	}
	return (NULL);
}

int	ft_execve(char **envp, t_tokenlist *cmd)
{
	char	**args;
	char	*bin;

	args = currcmd_to_2d_array(cmd);
	bin = find_full_bin_path(args[0], envp);
	if (bin == NULL)
	{
		if (!ft_strcmp(args[0], "."))
			ft_dprintf(STDERR_FILENO,
				"%s: filename argument required\n", args[0]);
		else if (ft_strchr(args[0], '/') && !has_alpha(args[0]))
			ft_dprintf(STDERR_FILENO, "%s: is a directory\n", args[0]);
		else if (ft_strchr(args[0], '/'))
			ft_dprintf(STDERR_FILENO,
				"%s: No such file or directory\n", args[0]);
		else if (ft_strlen(args[0]) == 0)
			ft_dprintf(STDERR_FILENO, "\'\': command not found\n");
		else
			ft_dprintf(STDERR_FILENO, "%s: command not found\n", args[0]);
		free_double_arr(args);
		return (127);
	}
	execve(bin, args, envp);
	free_double_arr(args);
	return (-1);
}
