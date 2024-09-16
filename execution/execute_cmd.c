/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:28:38 by qtay              #+#    #+#             */
/*   Updated: 2024/09/16 17:24:48 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
# include <linux/limits.h>

/**
 * Function to see what file an FD is referring to
 */
// void	print_fd_filename(int fd)
// {
//     char	path[PATH_MAX];
//     char	filename[PATH_MAX];
// 	ssize_t	len;

// 	snprintf(path, sizeof(path), "/proc/self/fd/%d", fd);
// 	len = readlink(path, filename, sizeof(filename) - 1);
//     if (len != -1)
// 	{
// 		filename[len] = '\0';
// 		printf("File descriptor %d refers to: %s\n", fd, filename);
//     }
// 	else
// 		perror("readlink");
// }

void	handle_normcmd(int prev_pipefd[], t_tokenlist **cmdlist)
{
	int				redir_fds[2];
	int				oristdio[2];
	int				exitcode;

	store_oristdio(oristdio);
	if (get_redirfds(redir_fds, cmdlist) == -1)
		return ;
	set_normcmd_redir(redir_fds[0], redir_fds[1]);
	if (prev_pipefd[0] == 0 && is_builtin(*cmdlist))
		// set_exit_status(run_cmd(*cmdlist));
		exit(1);
	else
	{
		if (create_fork() == 0)
		{
			read_from_pipe(prev_pipefd, redir_fds[0]);
			// exit(run_cmd(*cmdlist));
			exit(1);
		}
		close_pipes(prev_pipefd);
	}
	restore_oristdio(oristdio);
	config_signals();
}

void	handle_pipecmd(int pipefd[], int prev_pipefd[], t_tokenlist **cmdlist)
{
	char	path[100];
	int	redir_fds[2];
	// int	origio[2];

	if (get_redirfds(redir_fds, cmdlist) == 1)
		return ;
	// init_origio(origio);
	if (create_fork() == 0) 
	{
		child_redir(pipefd, prev_pipefd, redir_fds);
		// print_fd_filename(0);
		// exit(run_cmd(*cmdlist));
		exit(1);
	}
	else
		store_pipefd(pipefd, prev_pipefd);
	if (redir_fds[0] != 0)
		close(redir_fds[0]);
	if (redir_fds[1] != 0)
		close(redir_fds[1]);
	// restore_originalfd(origio[0], origio[1]);
	config_signals();
}


void	exec_cmdlist(int prev_pipefd[], t_tokenlist **cmdlist, bool with_pipe)
{
	int pipefd[2];

	if (with_pipe)
	{
		if (pipe(pipefd) == -1)
		{
			dprintf(STDERR_FILENO, "pipe failed for pipefd\n");
			exit(1);
		}
		handle_pipecmd(pipefd, prev_pipefd, cmdlist);
	}
	else
		handle_normcmd(prev_pipefd, cmdlist);
}
