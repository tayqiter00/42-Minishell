/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:18:14 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:30:25 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_dollarsign(int c)
{
	return (c == '$');
}

bool	is_pipe(int c)
{
	return (c == '|');
}

bool	is_blank(int c)
{
	return (c == ' '
		|| c == '\t'
		|| c == '\n');
}

bool	is_newline(int c)
{
	return (c == '\n');
}

/**
 * Last param as ft_strlen(token) is more robust for this stage but won't work
 * for initial tokenization.
 */
bool	is_redir(char *token)
{
	return (!ft_strcmp(token, "<<")
		|| !ft_strcmp(token, ">>")
		|| !ft_strcmp(token, "<")
		|| !ft_strcmp(token, ">"));
}
