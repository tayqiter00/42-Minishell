/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:18:22 by qtay              #+#    #+#             */
/*   Updated: 2024/09/30 23:01:57 by qtay             ###   ########.fr       */
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

bool    is_append(char *token)
{
	return (!ft_strncmp(token, ">>", ft_strlen(token)));	
}

bool    is_outfile(char *token)
{
	return (!ft_strncmp(token, ">", ft_strlen(token)));	
}

bool	is_builtin(t_tokenlist *cmdlist)
{
	char	*cmd;

	if (cmdlist->head == NULL)
		return (false);
	cmd = cmdlist->head->token;
	if (!ft_strncmp(cmd, "echo", ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, "cd", ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, "pwd", ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, "export", ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, "unset", ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, "env", ft_strlen(cmd)))
		return (true);
	if (!ft_strncmp(cmd, "exit", ft_strlen(cmd)))
		return (true);
	return (false);
}
