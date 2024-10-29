/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:38:28 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:31:15 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_num_env(char **envp)
{
	int	num;

	num = 0;
	while (envp && envp[num++])
		;
	return (num - 1);
}

void	free_double_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
}

/**
 * Need to duplicate envp since we're starting a new process and can only
 * modify our duplicated envp. 
 */
char	**dup_envp(char **envp)
{
	int		i;
	int		num_env;
	char	**buf;

	i = 0;
	num_env = count_num_env(envp);
	buf = ft_calloc(num_env + 1, sizeof(char *));
	while (i < num_env)
		buf[i++] = ft_strdup(*envp++);
	return (buf);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char **new_envp = dup_envp(envp);
// 	while (new_envp && *new_envp)
// 	{
// 		printf("%s\n", *new_envp);
// 		*new_envp++;	
// 	}
// }
