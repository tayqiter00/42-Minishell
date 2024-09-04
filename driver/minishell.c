/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 13:43:41 by qtay              #+#    #+#             */
/*   Updated: 2024/09/04 17:33:48 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_tokenlist(t_tokenlist *tokenlist)
{
	t_tokennode	*node;
	t_tokennode	*temp;

	node = tokenlist->head;
	if (!node) // check
	{
		free(tokenlist);
		return ;
	}
	temp = node;
	while (temp)
	{
		temp = node->next;
		free(node->token);
		free(node);
		node = temp;
	}
	free(tokenlist);
}

int	main(int ac, char **av, char **envp)
{
	char		*input;
	t_tokenlist	*tokenlist;

	((void)ac, (void)av);
	envp = dup_envp(envp);
	while (true)
	{
		config_signals();
		input = read_inputline();
		tokenlist = get_tokenlist(input, envp); // envp for variable expansion
	// while (tokenlist->head)
	// {
	// 	printf("%s\n", tokenlist->head->token);
	// 	// printf(" Is metachar?: %d\n", tokenlist->head->is_meta_char);
	// 	// if (tokenlist->head->is_meta_char)
	// 	// 	printf("\033[32m Is metachar\033[0m\n");
	// 	// else
	// 	// 	printf("\033[31m Not metachar\033[0m\n");
	// 	tokenlist->head = tokenlist->head->next;
	// }
		free(input);
		free_tokenlist(tokenlist);
	}
	free_double_arr(envp);
	return (EXIT_SUCCESS);
}
