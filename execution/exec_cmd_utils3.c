/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 20:25:01 by qtay              #+#    #+#             */
/*   Updated: 2024/09/09 20:25:22 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	restore_oristdio(int ori_stdio[])
{
	dup2(ori_stdio[0], STDIN_FILENO);
	close(ori_stdio[0]);
	dup2(ori_stdio[1], STDOUT_FILENO);
	close(ori_stdio[1]);
}

void	close_pipes(int prev_pipefd[])
{
	if (prev_pipefd[0] != 0)
	{
		close(prev_pipefd[0]);
		close(prev_pipefd[1]);
	}
}

void	read_from_pipe(int prev_pipefd[], int infilefd)
{
	if (prev_pipefd[0] != 0)
	{
		close(prev_pipefd[1]);
		if (infilefd == 0)
			dup2(prev_pipefd[0], STDIN_FILENO);
		close(prev_pipefd[0]);
	}
}

void	set_normcmd_redir(int infilefd, int outfilefd)
{
	if (infilefd != 0)
	{
		dup2(infilefd, STDIN_FILENO);
		close(infilefd);
	}
	if (outfilefd != 0)
	{
		dup2(outfilefd, STDOUT_FILENO);
		close(outfilefd);
	}
}

void	store_oristdio(int ori_stdio[])
{
	ori_stdio[0] = dup(STDIN_FILENO);
	ori_stdio[1] = dup(STDOUT_FILENO);
}
