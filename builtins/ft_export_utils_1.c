/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:19:14 by xquah             #+#    #+#             */
/*   Updated: 2024/10/12 20:25:32 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int count_valid_args(char **envp, t_tokennode *args)
{
	int valid_args_count;
	t_tokennode *current_arg;

	valid_args_count = 0;
	current_arg = args;
	while (current_arg)
	{
		if (entry_has_valid_name(current_arg->token))
		{
			if (is_not_duplicate(envp, current_arg->token))
				valid_args_count++;
		}
		current_arg = current_arg->next;
	}
	return (valid_args_count);
}

char	**realloc_envp(char **envp, size_t size_new)
{
	int		i;
	int		num_env;
	char	**buf;
	char	**temp;

	i = 0;
	num_env = count_num_env(envp);
	buf = calloc(size_new, sizeof(char *)); // ft_calloc()
	if (!buf)
		return NULL; // Handle allocation failure
	temp = envp;
	while (i < num_env)
		buf[i++] = ft_strdup(*temp++);
	free_double_arr(envp);
	return (buf);
}

void handle_duplicate(char **envp, char *args)
{
	bool has_equal;
	int args_name_len;

	has_equal = (bool)ft_strchr(args, '=');
	if (has_equal)
	{
		while (*envp)
		{
			args_name_len = ft_strcspn(args, "=");
			if (!ft_strncmp(*envp, args, args_name_len))
			{
				free(*envp);
				*envp = ft_strdup(args);
				break;
			}
			envp++;
		}
	}
}

void add_valid_args(char **envp, t_tokennode *args)
{
	int envp_count;
	t_tokennode *current_arg;

	envp_count = count_num_env(envp);
	current_arg = args;
	while (current_arg)
	{
		if (entry_has_valid_name(current_arg->token))
		{
			if (is_not_duplicate(envp, current_arg->token))
				envp[envp_count++] = ft_strdup(current_arg->token);
			else
				handle_duplicate(envp, current_arg->token);
		}
		else
			printf("'%s' is not a valid identifier\n", args->token);
		current_arg = current_arg->next;
	}
	envp[envp_count] = NULL;
}

void	insert_valid_args(char ***envp, t_tokennode *args)
{
	int envp_count;
	int valid_args_count;
	int old_size;
	int new_size;

	envp_count = count_num_env(*envp);
	valid_args_count = count_valid_args(*envp, args);
	old_size = sizeof(char *) * (envp_count + 1);
	new_size = sizeof(char *) * (envp_count + valid_args_count + 1);
	*envp = realloc_envp(*envp, new_size);
	if (!*envp)
	{
		printf("malloc failed for *envp\n");
		exit(-1);
	}
	add_valid_args(*envp, args);
}