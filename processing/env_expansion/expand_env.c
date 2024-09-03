/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:15:10 by qtay              #+#    #+#             */
/*   Updated: 2024/09/03 00:46:38 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	count_leading_chars(char *token, char *env)
{
	return (strstr(token, env) - token); // ft_strstr()
}

/**
 * Valgrind says theres a leak happening here but i cant find it
 */
int	count_env_len(char *env, char **envp)
{
	char	*env_name;
	int		ret_len;

	env_name = ft_strjoin(env + 1, "=");
	while (envp && *envp)
	{
		if (ft_strncmp(*envp, env_name, ft_strlen(env_name)) == 0)
		{
			ret_len = ft_strlen(*envp + ft_strlen(env_name));
			free(env_name);
			return (ret_len);
		}
		*envp++;
	}
	return (ft_strlen(env));
}

/**
 * A single token might contain several $
 */
int		count_expanded_len(char *token, char **envp)
{
	int		len;
	char	*env;

	len = 0;
	env = get_next_env(token);
	while (env)
	{
		len += count_leading_chars(token, env);
		len += count_env_len(env, envp); // alr freed
		token += count_leading_chars(token, env) + ft_strlen(env); // consider declaring new var
		free(env);
		env = get_next_env(NULL);
	}
	free(env); // check if needed
	return (len + ft_strlen(token));
}

char	*expand_env(char *token, char **envp)
{
	int		expanded_len;
	char	*result;

	expanded_len = count_expanded_len(token, envp);
	result = calloc((expanded_len + 1), sizeof(char)); // ft_calloc()
	if (!result)
	{
		dprintf(STDERR_FILENO, "malloc failed for expanded env\n"); // ft_dprintf(), free and exit
	}
	dup_expanded_token(result, token, envp);
	if (*result)
	{
		free(token);
		return (result);
	}
	free(result);
	return (token);
}
// int	main(int ac, char **av, char **envp)
// {
// 	char	*token;

// 	token = readline("> ");
// 	token = expand_env(token, envp);
// 	printf("%s\n", token);
// 	free(token);
// }
