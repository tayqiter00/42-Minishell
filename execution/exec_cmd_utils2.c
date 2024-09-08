/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:12:22 by qtay              #+#    #+#             */
/*   Updated: 2024/09/08 14:58:38 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
# include <sys/stat.h>


void	store_oristdio(int ori_stdio[2])
{
	ori_stdio[0] = dup(STDIN_FILENO);
	ori_stdio[1] = dup(STDOUT_FILENO);
}

pid_t	create_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		dprintf(STDERR_FILENO, "fork failed for pid\n"); // ft
		exit(EXIT_FAILURE);
	}
	return (pid);
}

/**
 * Only set for infile
 */
int	set_infile_redir(int redir_fds[2])
{
	if (redir_fds[0] != 0)
	{
		dup2(redir_fds[0], STDIN_FILENO);
		close(redir_fds[0]);
	}
}

int	set_stdout_redir(int pipefd[2], int redir_fds[2])
{
	if (pipefd)
	{
		close(pipefd[R_END]);
		dup2(pipefd[W_END], STDOUT_FILENO);
		close(pipefd[W_END]);
	}
	if (redir_fds[1] != 0)
	{
		dup2(redir_fds[1], STDOUT_FILENO);
		close(redir_fds[1]);
	}
}

int	parent_stdio_redir(int pipefd[2], int redir_fds[2])
{
    struct stat st;

	waitpid(-1, NULL, 0);
	close(pipefd[W_END]);
	dup2(pipefd[R_END], STDIN_FILENO); // 0 now points to pipe_read
	close(pipefd[R_END]);
	if (redir_fds[0] != 0)
	{
		close(redir_fds[0]);
		if (stat("minishell_temp.txt", &st) == 0)
		{
			if (st.st_mode & S_APPEND)	
				unlink("minishell_temp.txt");
		}
	}
	if (redir_fds[1] != 0)
		close(redir_fds[1]);
}
