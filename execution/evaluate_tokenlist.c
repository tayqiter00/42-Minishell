/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tokenlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 05:55:09 by qtay              #+#    #+#             */
/*   Updated: 2024/09/10 18:26:09 by qtay             ###   ########.fr       */
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

void	wait_for_child(void)
{
	int	exit_status;

	while (waitpid(-1, &exit_status, 0) > 0)
		set_exit_status(WEXITSTATUS(exit_status));
}

/**
 * how to make sure it's not "|" 
 */
void	eval_tokenlist(t_tokenlist *tokenlist, int heredoc_count)
{
	t_tokenlist	*cmdlist;
	int			prev_pipefd[2];

	ft_bzero(prev_pipefd, sizeof(int) * 2);
	while (tokenlist && tokenlist->head)
	{
		cmdlist = create_tokenlist();
		while (tokenlist->head && !is_pipe(*(tokenlist->head->token)))
			link_tokenlist(pop_tokennode(tokenlist), cmdlist);
		exec_cmdlist(prev_pipefd, &cmdlist, tokenlist->head);
		if (tokenlist->head)
			free_tokennode(pop_tokennode(tokenlist));
		free_tokenlist(cmdlist);
	}
	wait_for_child();
}
