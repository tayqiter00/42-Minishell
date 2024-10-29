/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:12:22 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 11:47:29 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_outfile_err(int outfilefd, t_tokennode *next)
{
	if (outfilefd != 0)
		close(outfilefd);
	if (!next)
	{
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token\n");
		set_exit_status(2);
		return (-1);
	}
	return (0);
}

void	print_err(char *filename)
{
	ft_dprintf(STDERR_FILENO, "%s: Is a directory\n", filename);
}

int	handle_infile_err(int infilefd, t_tokennode *next)
{
	if (infilefd != 0)
		close(infilefd);
	if (!next)
	{
		ft_dprintf(STDERR_FILENO,
			"syntax error near unexpected token\n");
		set_exit_status(2);
		return (-1);
	}
	return (0);
}

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
