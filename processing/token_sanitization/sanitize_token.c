/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sanitize_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:09:15 by qtay              #+#    #+#             */
/*   Updated: 2024/09/03 18:23:21 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_escapable(int c)
{
	return (c == '$'
		|| c == '\n'
		|| c == '"'
		|| c == '\\');
}

/**
 * The outer most quotes that aren't escaped should be removed
 */
void	dup_sanitized_token(char *result, char *token)
{
	bool	in_quote;
	int		quote_type;
	bool	should_escape;
	
	in_quote = false;
	quote_type = '\0';
	should_escape = false;
	while (*token)
	{
		if (is_backslash(*token) && !should_escape && (!is_quote(quote_type)
			|| (is_doublequote(quote_type) && is_escapable(*(token + 1)))))
			should_escape = true;
		else if (!should_escape && is_singlequote(*token) && quote_type != '"')
			set_in_quote(*token, &in_quote, &quote_type);
		else if (!should_escape && is_doublequote(*token) && quote_type != '\'')
			set_in_quote(*token, &in_quote, &quote_type);
		else
		{
			*result = *token;
			result++;
			should_escape = false;
		}
		token++;
	}
}

/**
 * echo "\'" should give \' but echo "\"" should give "
 * Don't sanitize if it's heredoc's node which comes after << (not yet handled)
 */
char	*sanitize_token(char *token)
{
	char	*result;

	result = calloc(ft_strlen(token) + 1, sizeof(char));
	if (!result)
	{
		dprintf(STDERR_FILENO, "malloc failed for removed quotes\n"); // ft_dprintf()
		exit(MALLOC_ERROR);
	}
	dup_sanitized_token(result, token);
	free(token);
	return(result);
}

