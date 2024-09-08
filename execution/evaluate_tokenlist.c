/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   evaluate_tokenlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 05:55:09 by qtay              #+#    #+#             */
/*   Updated: 2024/09/06 23:40:05 by qtay             ###   ########.fr       */
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
 *  how to make sure it's not "|"
 * 
 * Leaks happening after I added exec_cmdlist(). Still struggling to find it.
 */
void	eval_tokenlist(t_tokenlist *tokenlist)
{
	t_tokenlist	*cmdlist;

	while (tokenlist && tokenlist->head)
	{
		cmdlist = create_tokenlist();
		while (tokenlist->head && !is_pipe(*(tokenlist->head->token)))
			link_tokenlist(pop_tokennode(tokenlist), cmdlist);
		exec_cmdlist(&cmdlist, tokenlist->head);
		if (tokenlist->head)
			free_tokennode(pop_tokennode(tokenlist));
		free_tokenlist(cmdlist);
	}
}
