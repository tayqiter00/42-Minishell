/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:26:00 by qtay              #+#    #+#             */
/*   Updated: 2024/09/03 00:46:29 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * We're only handling valid env variables and $?
 * Not gonna handle $$, $!, $#, $*, $& and any non-env variables
 */
bool	is_valid_env(char *token)
{
	return (is_dollarsign(*token)
		&& (ft_isalnum(*(token + 1))
		|| is_underscore(*(token + 1))
		|| is_questionmark(*(token + 1))));
}

bool	is_valid_key(int c)
{
	return (ft_isalnum(c) || is_underscore(c));
}

/**
 * Returns an empty string if no unescaped '$' sign is found
 */
char	*get_env_start(char *token)
{
	bool	in_quote;
	int		quote_type;
	bool	should_escape;
	
	in_quote = false;
	quote_type = '\0';
	should_escape = false;
	while (*token)
	{
        if (is_backslash(*token) && !is_singlequote(quote_type) && !should_escape)
            should_escape = true;
        else if (is_quote(*token) && !should_escape)
            set_in_quote(*token, &in_quote, &quote_type);
        else if (!should_escape && !is_singlequote(quote_type) && is_valid_env(token))
            break ;
        else if (should_escape)
            should_escape = false;
        token++;		
	}
	return (token);
}

/**
 * Returns an empty string if no unescaped '$' sign is found
 */
char	*skip_env_key(char *env)
{
	if (is_dollarsign(*env))
	{
		env++;
		if (is_questionmark(*env))
			return (env + 1);
		while (*env && is_valid_key(*env))
			env++;
	}
	return (env);
}

char	*get_next_env(char *token)
{
	static char	*remaining;
	char		*env;

	if (token != NULL)
		remaining = token;
	if (!remaining || *remaining == '\0')
		return (NULL);
	env = get_env_start(remaining);
	remaining = skip_env_key(env);
	if (remaining == env)
		return (NULL);
	return (ft_substr(env, 0, remaining - env));
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*token;
// 	char	*env;

// 	token = readline("minishell> ");
// 	env = get_next_env(token);
// 	while (env)
// 	{
// 		printf("%s\n", env);
// 		env = get_next_env(NULL);
// 	}
// }
