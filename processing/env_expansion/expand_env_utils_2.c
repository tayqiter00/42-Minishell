/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:43:42 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 12:16:38 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Just added $?
 */
void	dup_env_value(char *expanded_env, char *env, char **envp)
{
	char	*env_name;

	if (ft_strncmp(env, "$?", ft_strlen(env)) == 0)
	{
		env_name = ft_itoa(get_exit_status());
		ft_strlcat(expanded_env, env_name, sizeof(expanded_env));
		free(env_name);
		return ;
	}
	env_name = ft_strjoin(env + 1, "=");
	while (envp && *envp)
	{
		if (ft_strncmp(*envp, env_name, ft_strlen(env_name)) == 0)
		{
			ft_strlcat(expanded_env, *envp + ft_strlen(env_name),
				sizeof(expanded_env));
			free(env_name);
			return ;
		}
		envp++;
	}
	free(env_name);
	ft_strlcat(expanded_env, "", sizeof(expanded_env));
}

void	handle_dollarsign_dup(char **expanded_env, char **token, char **envp)
{
	char	*env;

	env = get_next_env(*token);
	if (env)
	{
		dup_env_value(*expanded_env, env, envp);
		*token += ft_strlen(env);
		free(env);
		env = get_next_env(NULL);
	}
	else
		(*token)++;
}

void	dup_expanded_token(char *expanded_env, char *token, char **envp)
{
	bool	in_quote;
	int		quote_type;

	in_quote = false;
	quote_type = '\0';
	if (!token)
		return ;
	while (*token)
	{
		if ((!is_dollarsign(*token) && !is_quote(*token))
			|| (is_dollarsign(*token) && is_singlequote(quote_type)))
			;
		else if (is_dollarsign(*token))
		{
			handle_dollarsign_dup(&expanded_env, &token, envp);
			continue ;
		}
		else if (is_quote(*token))
			set_in_quote(*token, &in_quote, &quote_type);
		expanded_env[ft_strlen(expanded_env)] = *token;
		token++;
	}
}
