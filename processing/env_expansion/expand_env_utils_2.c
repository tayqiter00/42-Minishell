/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:43:42 by qtay              #+#    #+#             */
/*   Updated: 2024/09/03 00:46:33 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	dup_leading_chars(char *expanded_env, char *token, char *env)
{
	int	init_len;

	init_len = ft_strlen(expanded_env);
	while (strstr(token, env))
	{
		if (*token == '$') // better way to do this?
			break ;
		expanded_env[init_len] = *token;
		init_len++;
		token++;
	}
}

void	dup_env_value(char *expanded_env, char *env, char **envp)
{
	char	*env_name;

	env_name = ft_strjoin(env + 1, "=");
	while (envp && *envp)
	{
		if (ft_strncmp(*envp, env_name, ft_strlen(env_name)) == 0)
		{
			strcat(expanded_env, *envp + ft_strlen(env_name)); // define ft_strcat()
			free(env_name);
			return ;
		}
		*envp++;
	}
	free(env_name);
	strcat(expanded_env, env); // define ft_strcat()
}

void	dup_expanded_token(char *expanded_env, char *token, char **envp)
{
	char	*env;

	env = get_next_env(token);
	while (env)
	{
		dup_leading_chars(expanded_env, token, env);
		dup_env_value(expanded_env, env, envp);
		token += count_leading_chars(token, env) + ft_strlen(env);
		free(env);
		env = get_next_env(NULL);
	}
	free(env);
}
