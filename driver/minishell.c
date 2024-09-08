/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:43:41 by qtay              #+#    #+#             */
/*   Updated: 2024/09/08 16:59:10 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	free_tokenlist(t_tokenlist *tokenlist)
// {
// 	t_tokennode	*node;
// 	t_tokennode	*temp;

// 	if (!tokenlist)
// 		return ;
// 	node = tokenlist->head;
// 	if (!node) // check
// 	{
// 		free(tokenlist);
// 		return ;
// 	}
// 	temp = node;
// 	while (temp)
// 	{
// 		temp = node->next;
// 		free(node->token);
// 		free(node);
// 		node = temp;
// 	}
// 	free(tokenlist);
// }

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
 * Note: readline() will causes memory leak but it's fine.
 */
int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_tokenlist	*tokenlist;
	t_tokennode	*saved;

	((void)ac, (void)av);
	envp = dup_envp(envp);
	while (true)
	{
		config_signals();
		input = read_inputline();
		tokenlist = get_tokenlist(input, envp); // envp for variable expansion
		eval_tokenlist(tokenlist);
		// saved = tokenlist->head;
		// while (saved)
		// {
		// 	printf("%s\n", tokenlist->head->token);
		// 	saved = saved->next;
		// }
		free(input);
		free_tokenlist(tokenlist); // KIV, might not be needed
	}
	free_double_arr(envp);
	return (EXIT_SUCCESS);
}

