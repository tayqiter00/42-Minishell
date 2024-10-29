/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokenlist_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 12:23:25 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 12:24:36 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*process_token(char *token, char **envp, bool *heredoc_file,
		bool *metachar)
{
	if (is_metachar(token))
		*metachar = true;
	if (is_heredoc(token) && !(*heredoc_file))
		*heredoc_file = true;
	else if (*heredoc_file)
	{
		token = create_heredoc(token, envp, *metachar);
		if (!token)
			return (NULL);
		*heredoc_file = false;
	}
	else
	{
		token = expand_env(token, envp);
		token = sanitize_token(token);
	}
	return (token);
}
