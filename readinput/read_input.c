/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:48:19 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 10:29:14 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Note: "'" and '"' are considered as closed quotes so must ensure in_quote
 * is FALSE before setting it to TRUE
 */
void	set_in_quote(int c, bool *in_quote, int *quote_type)
{
	if (c == *quote_type)
	{
		*in_quote = false;
		*quote_type = '\0';
	}
	else if (*in_quote == false)
	{
		*in_quote = true;
		*quote_type = c;
	}
}

/**
 * Single quotes preserve the literal values of the characters.
 * Double quotes preserve most characters' literal values except $, \ and `.
 * The backslash in double quotes retains its special meaning only when
 * followed by one of the following characters: ‘$’, ‘`’, ‘"’, ‘\’, or
 * newline.
 * E.g., echo "\"" gives " but echo "\'" gives \'
 */
static bool	unclosed_quotes(char *input)
{
	bool	in_quote;
	int		quote_type;
	bool	should_escape;

	in_quote = false;
	quote_type = '\0';
	should_escape = false;
	while (*input)
	{
		if (is_backslash(*input) && !is_singlequote(quote_type)
			&& !should_escape)
			should_escape = true;
		else if (is_quote(*input) && !should_escape)
			set_in_quote(*input, &in_quote, &quote_type);
		else if (should_escape)
			should_escape = false;
		input++;
	}
	return (in_quote);
}

char	*read_inputline(void)
{
	char	*input;

	input = NULL;
	if (isatty(STDIN_FILENO))
		input = readline("minishell> ");
	if (input == NULL)
	{
		ft_dprintf(STDERR_FILENO, "exit\n");
		exit(EXIT_FAILURE);
	}
	add_history(input);
	if (unclosed_quotes(input))
	{
		ft_dprintf(STDERR_FILENO, "syntax error: unclosed quotes found\n");
		set_exit_status(SYNTAX_ERROR);
		return (NULL);
	}
	return (input);
}

// int main()
// {
//     char    *input;

//     while (1)
//     {
//         input = read_inputline();
//     }
// }