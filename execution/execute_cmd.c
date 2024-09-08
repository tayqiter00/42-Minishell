/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:28:38 by qtay              #+#    #+#             */
/*   Updated: 2024/09/08 17:15:25 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_normcmd(t_tokenlist **cmdlist)
{
	int	redir_fds[2];

	if (get_redirfds(redir_fds, cmdlist) == -1)
		return ;
	if (set_infile_redir(redir_fds) == -1)
		return ;
	if (set_stdout_redir(NULL, redir_fds) == -1)
		return ;
	if (isatty(STDIN_FILENO) && is_builtin(*cmdlist)) // not a pipe
	{
		set_exit_status(exec_cmd(*cmdlist)); // to define exec_cmd()
		exit(get_exit_status());	
	}
	else if (create_fork() == 0)
	{
		set_exit_status(exec_cmd(*cmdlist)); // to define exec_cmd()
		exit(get_exit_status());
	}
	waitpid(-1, NULL, 0);
	if (redir_fds[0] != 0)
		close(redir_fds[0]);
	if (redir_fds[1] != 0)
		close(redir_fds[1]);
}

void	handle_pipecmd(int pipefd[2], t_tokenlist **cmdlist)
{
	int	redir_fds[2];
	// int	ori_stdio[2];

	if (get_redirfds(redir_fds, cmdlist) == -1)
		return ;
	// store_oristdio(ori_stdio);
	if (set_infile_redir(redir_fds) == -1)
		return ;
	if (create_fork() == 0)
	{
		set_stdout_redir(pipefd, redir_fds);
		set_exit_status(exec_cmd(*cmdlist)); // to define exec_cmd()
		exit(get_exit_status());
	}
	parent_stdio_redir(pipefd, redir_fds);
}

void	exec_cmdlist(t_tokenlist **cmdlist, bool with_pipe)
{
	int pipefd[2];

	if (with_pipe)
	{
		if (pipe(pipefd) == -1)
		{
			dprintf(STDERR_FILENO, "pipe failed for pipefd\n"); // ft
			exit(1); // define pipe error
		}
		handle_pipecmd(pipefd, cmdlist);
	}
	else
		// handle_normcmd(cmdlist);
		return ; // place holder
}
