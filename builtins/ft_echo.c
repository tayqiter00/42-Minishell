/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:15:44 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:24:01 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_option_n(t_tokennode *args)
{
	char	*token;

	token = args->token;
	if (!ft_strncmp(token, "-n", 2))
	{
		token += 2;
		token += ft_strspn(token, "n");
		if (*token == '\0')
			return (true);
	}
	return (false);
}

/**
 * Taking into account cases like echo -nnn and echo -n -n -n
 */
void	print_tokens(t_tokennode *args)
{
	while (args && !args->is_meta_char)
	{
		if (is_option_n(args))
		{
			args = args->next;
			continue ;
		}
		printf("%s", args->token);
		args = args->next;
		if (args && !args->is_meta_char)
			printf(" ");
	}
}

/**
 * Thinking about how to handle: echo [metachar] which will give syntax error
 */
void	print_newline(t_tokennode *args)
{
	if (args == NULL || !is_option_n(args))
		printf("\n");
}

/**
 * echo prints everthing which comes after it, incl. echo "hello" "world",
 * unless its a non-escaped/quoted metacharacter
 * 
 * Just print a newline if no args after newline
 * 
 * echo with option -n doesn't output the trailing newline
 */
int	ft_echo(t_tokennode *args) // we gonna feed echo's args here
{
	print_tokens(args);
	print_newline(args);
	return (0);
}
