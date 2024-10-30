/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tokenlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 05:55:09 by qtay              #+#    #+#             */
/*   Updated: 2024/10/30 21:48:21 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tokennode	*pop_tokennode(t_tokenlist *tokenlist)
{
	t_tokennode	*popnode;

	if (tokenlist == NULL || tokenlist->head == NULL)
		return (NULL);
	popnode = tokenlist->head;
	tokenlist->head = tokenlist->head->next;
	popnode->next = NULL;
	return (popnode);
}

/**
 * First checks if child was terminated by a signal.
 * 
 * Technically, bash doesnt give 130 if you ctrl+C with pipe but a cmd runs
 */
int	wait_for_child(void)
{
	int		exit_status;
	bool	newline;
	bool	return_status;

	newline = false;
	return_status = SUCCESS;
	while (waitpid(-1, &exit_status, 0) > 0)
	{
		if (WIFSIGNALED(exit_status))
		{
			return_status = FAILURE;
			if (WTERMSIG(exit_status) == 3)
				ft_dprintf(STDERR_FILENO, "Quit: 3\n");
			else if (WTERMSIG(exit_status) == 2 && !newline)
			{
				newline = true;
				ft_dprintf(STDERR_FILENO, "\n");
			}
			set_exit_status(128 + WTERMSIG(exit_status));
		}
		else if (WIFEXITED(exit_status))
			set_exit_status(WEXITSTATUS(exit_status));
	}
	return (return_status);
}

/**
 * how to make sure it's not "|" 
 */
void	eval_tokenlist(t_tokenlist *tokenlist, char ***envp)
{
	t_tokenlist	*cmdlist;
	int			prev_pipefd[2];

	if (!tokenlist)
		return ;
	ft_bzero(prev_pipefd, sizeof(int) * 2);
	while (tokenlist && tokenlist->head)
	{
		cmdlist = create_tokenlist();
		while (tokenlist->head && (!is_pipe(*(tokenlist->head->token))
				|| (is_pipe(*(tokenlist->head->token))
					&& !tokenlist->head->is_meta_char)))
			link_tokenlist(pop_tokennode(tokenlist), cmdlist);
		if (exec_cmdlist(prev_pipefd, &cmdlist, tokenlist->head, envp))
		{
			free_tokenlist(cmdlist);
			return ;
		}
		if (tokenlist->head)
			free_tokennode(pop_tokennode(tokenlist));
		free_tokenlist(cmdlist);
	}
	wait_for_child();
}
