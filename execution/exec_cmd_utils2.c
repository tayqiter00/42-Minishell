/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:12:22 by qtay              #+#    #+#             */
/*   Updated: 2024/09/10 18:26:50 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
# include <sys/stat.h>

void	child_redir(int pipefd[], int prev_pipefd[], int redir_fds[])
{
	close(pipefd[0]);
	if (prev_pipefd[0] != 0)
	{
		close(prev_pipefd[1]);
		dup2(prev_pipefd[0], STDIN_FILENO);
		close(prev_pipefd[0]);
	}
	if (redir_fds[0] != 0)
	{
		dup2(redir_fds[0], STDIN_FILENO);
		close(redir_fds[0]);
	}
	if (redir_fds[1] != 0)
	{
		dup2(redir_fds[1], STDOUT_FILENO);
		close(redir_fds[1]);
	}
	else
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
}

void	store_pipefd(int pipefd[], int prev_pipefd[])
{
	if (prev_pipefd[0] != 0)
	{
		close(prev_pipefd[0]);
		close(prev_pipefd[1]);
	}
	prev_pipefd[0] = pipefd[0];
	prev_pipefd[1] = pipefd[1];
}
