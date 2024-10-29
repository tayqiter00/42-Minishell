/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:26:32 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 10:28:22 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

void	sort_envp(char **envp)
{
	int	i;
	int	j;
	int	len;

	len = count_num_env(envp);
	i = 1;
	while (i < len)
	{
		j = i;
		while (j > 0 && ft_strcmp(envp[j - 1], envp[j]) > 0)
		{
			ft_swap(&envp[j - 1], &envp[j]);
			j--;
		}
		i++;
	}
}

void	print_export_envp(char **envp)
{
	char	*name;
	char	*value;

	while (*envp)
	{
		if ((is_underscore(**envp) && *(*envp + 1) == '=')
			|| is_special_env_name(**envp))
		{
			envp++;
			continue ;
		}
		name = ft_strndup(*envp, ft_strcspn(*envp, "="));
		value = ft_strchr(*envp, '=');
		if (value)
		{
			value++;
			printf("declare -x %s=\"%s\"\n", name, value);
		}
		else if (name && *name)
			printf("declare -x %s\n", name);
		free(name);
		envp++;
	}
}
/**
 * Format: export [name[=value]]
 * 
 * Mark each shell var [name] to be passed to child processes in the
 * enviroment.
 * 
 * If no names are supplied, a list of names of all exported variables is
 * displayed.
 * 
 * If a variable name is followed by =value, the value of the v
*/

int	ft_export(t_tokennode *args, char ***envp)
{
	char	**d_envp;

	insert_valid_args(envp, args);
	d_envp = dup_envp(*envp);
	sort_envp(d_envp);
	if (args == NULL)
		print_export_envp(d_envp);
	free_double_arr(d_envp);
	return (0);
}
