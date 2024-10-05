/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:15:10 by qtay              #+#    #+#             */
/*   Updated: 2024/10/05 22:55:23 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * Just added $?
 */
int	count_env_len(char *env, char **envp)
{
	char	*env_name;
	int		ret_len;

	if (ft_strncmp(env, "$?", ft_strlen(env)) == 0)
	{
		env_name = ft_itoa(get_exit_status());
		ret_len = ft_strlen(env_name);
		free(env_name);
		return (ret_len);
	}
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
	free(env_name);
	return (1);
}

/**
 * A single token might contain several $
 */
int		count_expanded_len(char *token, char **envp)
{
	int		len;
	char	*env;
	bool	in_quote;
	int		quote_type;
	
	len = 0;
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
				len += count_env_len(env, envp);
				token += ft_strlen(env);
				free(env);
				env = get_next_env(NULL);
				continue ;
			}
		}
        else if (is_quote(*token))
            set_in_quote(*token, &in_quote, &quote_type);
		len++;
        token++;
	}
	return (len);
}

char	*expand_env(char *token, char **envp)
{
	int		expanded_len;
	char	*result;

	expanded_len = count_expanded_len(token, envp);
	result = calloc((expanded_len + 1), sizeof(char)); // ft_calloc()
	if (!result)
	{
		dprintf(STDERR_FILENO, "malloc failed for expanded env\n");
		exit(MALLOC_ERROR);
	}
	dup_expanded_token(result, token, envp);
	free(token);
	return (result);

}
// int	main(int ac, char **av, char **envp)
// {
// 	char	*token;

// 	token = readline("> ");
// 	token = expand_env(token, envp);
// 	printf("%s\n", token);
// 	free(token);
// }
