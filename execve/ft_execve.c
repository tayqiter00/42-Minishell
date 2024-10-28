/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:00:46 by xquah             #+#    #+#             */
/*   Updated: 2024/10/28 14:34:34 by xquah            ###   ########.fr       */
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

static char	**currcmd_to_2d_array(t_tokenlist *currcmd)
{
	char		**result;
	t_tokennode	*current;
	int			i;

	result = malloc(sizeof(char *) * (count_cmdlist(currcmd) + 1));
	if (result == NULL)
	{
		printf("malloc failed for result\n");
		exit(-1);
	}
	i = 0;
	current = currcmd->head;
	while (current)
	{
		result[i] = ft_strdup(current->token);
		if (result[i] == NULL)
		{
			printf("ft_strdup failed for result[%d]\n", i);
			exit(-1);
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
	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) != 0)
			continue ;
		path = ft_strtok(envp[i] + 5, ':');
		while (path)
		{
			if (bin[0] == '.' || bin[0] == '/')
				full_path = strjoin_sep(bin, "", "");
			else
				full_path = strjoin_sep(path, bin, "/");
			if (is_executable(full_path) && access(full_path, X_OK) == 0)
				return (full_path);
			free(full_path);
			path = ft_strtok(NULL, ':');
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
			printf("%s: filename argument required\n", args[0]);
		else if (ft_strchr(args[0], '/') && !has_alpha(args[0]))
			printf("%s: is a directory\n", args[0]);
		else if (ft_strchr(args[0], '/'))
			printf("%s: No such file or directory\n", args[0]);
		else if (ft_strlen(args[0]) == 0)
			return (printf("\'\': command not found\n"), 127);
		else
			return (dprintf(STDERR_FILENO, "%s: command not found\n", args[0]), 127);
		free_double_arr(args);
		return (-1);
	}
	execve(bin, args, envp);
	free_double_arr(args);
	return (-1);
}
