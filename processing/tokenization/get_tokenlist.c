/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokenlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:59:22 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 12:23:41 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokenlist	*create_tokenlist(void)
{
	t_tokenlist	*tokenlist;

	tokenlist = malloc(sizeof(t_tokenlist));
	if (tokenlist == NULL)
	{
		ft_dprintf(STDERR_FILENO, "malloc failed for create_tokenlist\n");
		exit(MALLOC_ERROR);
	}
	tokenlist->head = NULL;
	return (tokenlist);
}

/**
 * is_meta_char added cuz after we sanitize the tokens (remove quotes and
 * backslashes), we won't know if it should be treated as a metacharacter
 * anymore.
 */
t_tokennode	*create_tokennode(char *token, bool metachar)
{
	t_tokennode	*new_tokennode;

	if (!token)
		return (NULL);
	new_tokennode = malloc(sizeof(t_tokennode));
	if (new_tokennode == NULL)
	{
		ft_dprintf(STDERR_FILENO, "malloc failed for create_tokennode\n");
		exit(MALLOC_ERROR);
	}
	new_tokennode->token = token;
	new_tokennode->next = NULL;
	new_tokennode->is_meta_char = metachar;
	return (new_tokennode);
}

t_tokennode	*get_lastnode(t_tokenlist *tokenlist)
{
	t_tokennode	*last;

	last = tokenlist->head;
	while (last->next)
		last = last->next;
	return (last);
}

void	link_tokenlist(t_tokennode *tokennode, t_tokenlist *tokenlist)
{
	t_tokennode	*last;

	if (!tokennode || !tokenlist)
		return ;
	if (tokenlist->head == NULL)
		tokenlist->head = tokennode;
	else
	{
		last = get_lastnode(tokenlist);
		last->next = tokennode;
	}
}

/**
 * create_heredoc seems to work but still need to double check
 */
t_tokenlist	*get_tokenlist(char *input, char **envp)
{
	t_tokenlist	*tokenlist;
	char		*token;
	t_tokennode	*tokennode;
	bool		heredoc_file;
	bool		metachar;

	if (input == NULL)
		return (NULL);
	heredoc_file = false;
	tokenlist = create_tokenlist();
	token = get_next_token(input);
	while (token)
	{
		metachar = false;
		token = process_token(token, envp, &heredoc_file, &metachar);
		if (!token)
		{
			free_tokenlist(tokenlist);
			return (NULL);
		}
		tokennode = create_tokennode(token, metachar);
		link_tokenlist(tokennode, tokenlist);
		token = get_next_token(NULL);
	}
	return (tokenlist);
}

// int	main()
// {
// 	t_tokenlist	*tokenlist;
// 	char	*input;

// 	input = strdup("cmd1 cmd2 >> cmd3 | cmd4");
// 	tokenlist = get_tokenlist(input);
// }
