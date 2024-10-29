/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 16:11:49 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 23:11:14 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	skip_leading_whitespace(char *remaining)
{
	return (ft_strspn(remaining, WHITESPACE));
}

// bool    is_token(char *input)
// {
//     return (!ft_strncmp(input, "<", 1)
//         || !ft_strncmp(input, ">", 1)
//         || !ft_strncmp(input, "<<", 2)
//         || !ft_strncmp(input, ">>", 2)
//         || !ft_strncmp(input, "|", 1));
// }

/**
 * >> and << must come first
 */
int	token_len(char *input)
{
	if (!ft_strncmp(input, ">>", 2) || !ft_strncmp(input, "<<", 2))
		return (2);
	else if (!ft_strncmp(input, ">", 1) || !ft_strncmp(input, "<", 1)
		|| !ft_strncmp(input, "|", 1))
		return (1);
	return (0);
}

/**
 * The first is_token() handles where input starts with token
 * The second is_token() handles those in the middle
 * Notice how they differ in their return value
 * 
 * I changed is_token() to is_metachar(): order matters
 */
char	*get_token_end(char *input)
{
	bool	in_quote;
	int		quote_type;
	bool	should_escape;

	in_quote = false;
	quote_type = '\0';
	should_escape = false;
	if (is_metachar(input))
		return (input + token_len(input));
	while (*input)
	{
		if (is_backslash(*input) && !is_singlequote(quote_type)
			&& !should_escape)
			should_escape = true;
		else if (is_quote(*input) && !should_escape)
			set_in_quote(*input, &in_quote, &quote_type);
		else if (!should_escape && !in_quote
			&& (is_metachar(input) || is_blank(*input)))
			break ;
		else if (should_escape)
			should_escape = false;
		input++;
	}
	return (input);
}

char	*get_next_token(char *input)
{
	static char	*remaining;
	char		*token;

	if (input != NULL)
		remaining = input;
	if (remaining == NULL || *remaining == '\0')
		return (NULL);
	token = remaining;
	token += skip_leading_whitespace(remaining);
	remaining = get_token_end(token);
	if (token == remaining)
		return (NULL);
	return (ft_substr(token, 0, remaining - token));
}

// int	main()
// {
// 	char	*input = "		 example	>>  example";
// 	input = strdup(input);
// 	char	*token;

// 	token = get_next_token(input);
// 	while (token)
// 	{
// 		printf("%s\n", token);
// 		token = get_next_token(NULL);
// 	}
// }
