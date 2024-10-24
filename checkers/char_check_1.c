/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:17:59 by qtay              #+#    #+#             */
/*   Updated: 2024/10/22 12:09:49 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    is_heredoc(char *token)
{
	return (!ft_strcmp(token, "<<"));
}

bool    is_questionmark(int c)
{
    return (c == '?');
}

bool    is_backslash(int c)
{
    return (c == '\\');
}

bool	is_underscore(int c)
{
	return (c == '_');
}

bool	is_metachar(char *token)
{
	return (!ft_strncmp(token, "<<", 2)
		|| !ft_strncmp(token, ">>", 2)
		|| !ft_strncmp(token, "<", 1)
		|| !ft_strncmp(token, ">", 1)
		|| !ft_strncmp(token, "|", 1));
}
