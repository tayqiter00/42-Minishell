/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:43:41 by qtay              #+#    #+#             */
/*   Updated: 2024/09/22 12:46:35 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokennode(t_tokennode *node)
{
	if (node == NULL)
		return ;
	free_tokennode(node->next);
	free(node->token);
	free(node);
}

void	free_tokenlist(t_tokenlist *tokenlist)
{
	if (!tokenlist)
		return ;
	free_tokennode(tokenlist->head);
	free(tokenlist);
}

/**
 * Note: readline() will cause memory leak but it's fine.
 */
int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_tokenlist	*tokenlist;
	t_tokenlist	*saved;
	int			heredoc_count;

	((void)ac, (void)av);
	envp = dup_envp(envp);
	while (true)
	{
		config_signals();
		input = read_inputline();
		tokenlist = get_tokenlist(input, envp);
		heredoc_count = eval_heredocs(&tokenlist);
		eval_tokenlist(tokenlist, heredoc_count, envp);
		free(input);
		free_tokenlist(tokenlist);
		unlink_heredocs(heredoc_count);
	}
	free_double_arr(envp);
	return (EXIT_SUCCESS);
}
