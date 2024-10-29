/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:49:19 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 11:51:39 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_heredoc_child(char *delim, char **envp, int heredoc_fd,
	bool has_quotes)
{
	char	*input;

	default_signals();
	while (true)
	{
		input = readline("heredoc> ");
		if (!ft_strcmp(input, delim))
			break ;
		if (input == NULL)
		{
			ft_dprintf(STDERR_FILENO,
				"warning: here-document delimited by end-of-file\n");
			free(delim);
			exit(get_exit_status());
		}
		if (!has_quotes)
			input = expand_env(input, envp);
		write(heredoc_fd, input, ft_strlen(input));
		write(heredoc_fd, "\n", 1);
		free(input);
	}
	exit(get_exit_status());
}
