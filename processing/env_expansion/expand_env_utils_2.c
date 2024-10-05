/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:43:42 by qtay              #+#    #+#             */
/*   Updated: 2024/10/05 22:59:52 by qtay             ###   ########.fr       */
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
		env_name = ft_itoa(get_exit_status()); // malloc
		strcat(expanded_env, env_name); // ft_strcat()
		free(env_name);
		return ;
	}
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
	strcat(expanded_env, ""); // define ft_strcat()
}

void	dup_expanded_token(char *expanded_env, char *token, char **envp)
{
	char	*env;
	bool	in_quote;
	int		quote_type;
	
	in_quote = false;
	quote_type = '\0';
	env = get_next_env(token);
	while (*token)
	{
		if ((!is_dollarsign(*token) && !is_quote(*token)) || (is_dollarsign(*token) && is_singlequote(quote_type)))
			;
		else if (is_dollarsign(*token))
		{
			if (env)
			{
				dup_env_value(expanded_env, env, envp);
				token += ft_strlen(env);
				free(env);
				env = get_next_env(NULL);
			}
			else
				token++;
			continue ;
		}
        else if (is_quote(*token))
            set_in_quote(*token, &in_quote, &quote_type);
		expanded_env[ft_strlen(expanded_env)] = *token;
		token++;
	}
}
