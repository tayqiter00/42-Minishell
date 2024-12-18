/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:18:09 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:29:36 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_singlequote(int c)
{
	return (c == '\'');
}

bool	is_doublequote(int c)
{
	return (c == '\"');
}

bool	is_quote(int c)
{
	return (is_singlequote(c) || is_doublequote(c));
}

bool	is_infile(char *token)
{
	return (!ft_strcmp(token, "<"));
}

bool	is_question_mark(char c)
{
	return (c == '?');
}
