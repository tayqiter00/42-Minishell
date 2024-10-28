/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 02:28:38 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 13:36:34 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
# include <linux/limits.h>

/**
 * Add back char **envp as an argument once cd, 
 * unset and run execve has been finished
 */
int run_cmd(t_tokenlist *currcmd, char ***envp)
{
	char *cmd;
	t_tokennode *args;

	if (currcmd->head == NULL)
		return (0);
	default_signals();
	cmd = currcmd->head->token;
	args = currcmd->head->next;
	if (!ft_strcmp(cmd, "echo"))
		return (ft_echo(args));
	if (!ft_strcmp(cmd, "cd"))
		return (ft_cd(args, *envp));
	if (!ft_strcmp(cmd, "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(cmd, "export"))
		return (ft_export(args, envp));
	if (!ft_strcmp(cmd, "unset"))
		return (ft_unset(*envp, args));
	if (!ft_strcmp(cmd, "exit"))
		return (ft_exit(args));
	if (!ft_strcmp(cmd, "env"))
		return (ft_env(*envp));
	return (ft_execve(*envp, currcmd));
}

int handle_normcmd(int prev_pipefd[], t_tokenlist **cmdlist, char ***envp)
{
	int				redir_fds[2];
	int				oristdio[2];
	int				exitcode;
	pid_t			pid;

	store_oristdio(oristdio);
	if (get_redirfds(redir_fds, cmdlist) == -1)
		return (1);
	set_normcmd_redir(redir_fds[0], redir_fds[1]);
	if (prev_pipefd[0] == 0 && is_builtin(*cmdlist))
		set_exit_status(run_cmd(*cmdlist, envp));
	else
	{
		pid = create_fork();
		if (pid == 0)
		{
			read_from_pipe(prev_pipefd, redir_fds[0]);
			exit(run_cmd(*cmdlist, envp));
		}
		close_pipes(prev_pipefd);
	}
	ignore_signals();
	restore_oristdio(oristdio);
	return (0);
}

int	handle_pipecmd(int pipefd[], int prev_pipefd[], t_tokenlist **cmdlist, char ***envp)
{
	int		redir_fds[2];
	int		origio[2];
	pid_t	pid;

	if (get_redirfds(redir_fds, cmdlist) == -1)
		return (1);
	pid = create_fork();
	if (pid == 0)
	{
		child_redir(pipefd, prev_pipefd, redir_fds);
		exit(run_cmd(*cmdlist, envp));
	}
	store_pipefd(pipefd, prev_pipefd);
	if (redir_fds[0] != 0)
		close(redir_fds[0]);
	if (redir_fds[1] != 0)
		close(redir_fds[1]);
}

int	exec_cmdlist(int prev_pipefd[], t_tokenlist **cmdlist, bool with_pipe, char ***envp)
{
	int pipefd[2];

	if (with_pipe)
	{
		if (pipe(pipefd) == -1)
		{
			dprintf(STDERR_FILENO, "pipe failed for pipefd\n");
			exit(1);
		}
		return (handle_pipecmd(pipefd, prev_pipefd, cmdlist, envp));
	}
	else
		return (handle_normcmd(prev_pipefd, cmdlist, envp));
}
