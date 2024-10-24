/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:18:22 by qtay              #+#    #+#             */
/*   Updated: 2024/10/22 12:12:24 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_exclamation(char c)
{
	return (c == '!');
}

bool	is_ampersand(char c)
{
	return (c == '&');
}

bool	is_append(char *token)
{
	return (!ft_strcmp(token, ">>"));
}

bool	is_outfile(char *token)
{
	return (!ft_strcmp(token, ">"));
}

bool	is_builtin(t_tokenlist *cmdlist)
{
	char	*cmd;

	if (cmdlist->head == NULL)
		return (false);
	cmd = cmdlist->head->token;
	if (!ft_strcmp(cmd, "echo"))
		return (true);
	if (!ft_strcmp(cmd, "cd"))
		return (true);
	if (!ft_strcmp(cmd, "pwd"))
		return (true);
	if (!ft_strcmp(cmd, "export"))
		return (true);
	if (!ft_strcmp(cmd, "unset"))
		return (true);
	if (!ft_strcmp(cmd, "env"))
		return (true);
	if (!ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}
