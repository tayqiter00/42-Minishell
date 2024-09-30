/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:50:40 by qtay              #+#    #+#             */
/*   Updated: 2024/09/30 23:27:06 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

t_tokenlist	*extract_redirs(t_tokenlist **cmdlist)
{
	t_tokenlist	*redirlist;
	t_tokenlist	*cleaned_cmdlist;

	redirlist = create_tokenlist();
	cleaned_cmdlist = create_tokenlist();
	while (cmdlist && (*cmdlist)->head)
	{
		if (is_redir((*cmdlist)->head->token)
			&& (*cmdlist)->head->is_meta_char)
		{
			link_tokenlist(pop_tokennode(*cmdlist), redirlist);
			link_tokenlist(pop_tokennode(*cmdlist), redirlist);
		}
		else
			link_tokenlist(pop_tokennode(*cmdlist), cleaned_cmdlist);
	}
	free_tokenlist(*cmdlist);
	*cmdlist = cleaned_cmdlist;
	return (redirlist);
}
int	get_infilefd(t_tokenlist *redirlist)
{
	t_tokennode	*node;
	int			infilefd;
	char		*filename;

	node = redirlist->head;
	infilefd = 0;
	while (node)
	{
		if (is_heredoc(node->token) || is_infile(node->token))
		{
			if (infilefd != 0)
				close(infilefd);
			if (!node->next)
			{
				dprintf(STDERR_FILENO, "syntax error near unexpected token 'newline'\n");
				set_exit_status(2);
				return (-2);
			}
			filename = node->next->token;
			infilefd = open(filename, O_RDONLY, 0644);
			if (infilefd == -1)
			{
				dprintf(STDERR_FILENO, "%s: No such file or directory\n", filename); // ft
				set_exit_status(1);
				return (-1);
			}
		}
		node = node->next;
	}
	return (infilefd);
}

int	get_outfilefd(t_tokenlist *redirlist)
{
	t_tokennode	*node;
	int			outfilefd;
	char		*filename;

	node = redirlist->head;
	outfilefd = 0;
	while (node)
	{
		if (is_outfile(node->token) || is_append(node->token))
		{
			if (outfilefd != 0)
				close(outfilefd);
			if (!node->next)
			{
				dprintf(STDERR_FILENO, "syntax error near unexpected token 'newline'\n");
				set_exit_status(2);
				return (-2);
			}
			filename = node->next->token;
			if (is_outfile(node->token))
				outfilefd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else
				outfilefd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (outfilefd == -1)
			{
				dprintf(STDERR_FILENO, "%s: Is a directory\n", filename); // ft
				set_exit_status(1);
				return (-1);
			}
		}
		node = node->next;
	}
	return (outfilefd);
}

int	get_redirfds(int redir_fds[], t_tokenlist **cmdlist)
{
	t_tokenlist	*redirlist;

	redirlist = extract_redirs(cmdlist);
	redir_fds[0] = get_infilefd(redirlist); // redir_fds[INFILE]
	if (redir_fds[0] < 0)
	{
		set_exit_status(-1 * redir_fds[0]);
		free_tokenlist(redirlist);
		return (-1); // 
	}
	redir_fds[1] = get_outfilefd(redirlist); // redir_fds[OUTFILE]
	if (redir_fds[1] < 0)
	{
		set_exit_status(-1 * redir_fds[1]);
		free_tokenlist(redirlist);
		return (-1);
	}
	free_tokenlist(redirlist);
	return (0);
}
