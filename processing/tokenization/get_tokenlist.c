/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokenlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 15:59:22 by qtay              #+#    #+#             */
/*   Updated: 2024/10/24 12:25:25 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tokenlist *create_tokenlist(void)
{
    t_tokenlist *tokenlist;

    tokenlist = malloc(sizeof(t_tokenlist));
    if (tokenlist == NULL)
	{
        dprintf(STDERR_FILENO, "malloc failed for create_tokenlist\n");
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
t_tokennode *create_tokennode(char *token, bool metachar)
{
    t_tokennode *new_tokennode;

	if (!token)
		return (NULL);
    new_tokennode = malloc(sizeof(t_tokennode));
    if (new_tokennode == NULL)
	{
        dprintf(STDERR_FILENO, "malloc failed for create_tokennode\n");
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

void    link_tokenlist(t_tokennode *tokennode, t_tokenlist *tokenlist)
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

void initialize_processing_state(bool *heredoc_file, bool *metachar)
{
    *heredoc_file = false;
    *metachar = false;
}

void create_and_link_token_node(t_tokenlist *tokenlist, char *token, bool metachar)
{
    t_tokennode *tokennode;

    tokennode = create_tokennode(token, metachar);   // Create a new token node
    link_tokenlist(tokennode, tokenlist);            // Link the node to the token list
}

char *process_token(char *token, t_tokenlist *tokenlist, bool *heredoc_file, char **envp, bool *metachar)
{
    if (is_heredoc(token) && !(*heredoc_file))
    {
        *heredoc_file = true;
    }
    else if (*heredoc_file)
    {
        token = process_heredoc(token, tokenlist, envp, *metachar);
        *heredoc_file = false;
    }
    else
    {
        token = expand_and_sanitize_token(token, envp);
    }
    return token;
}

/**
 * create_heredoc seems to work but still need to double check
 */
t_tokenlist *get_tokenlist(char *input, char **envp)
{
    t_tokenlist *tokenlist;
    char        *token;
    bool        heredoc_file;
    bool        metachar;

    if (input == NULL)
        return NULL;
    tokenlist = create_tokenlist();      // Create a token list
    token = get_next_token(input);       // Get the first token
    initialize_processing_state(&heredoc_file, &metachar);  // Initialize state variables
    while (token)
    {
        update_metachar_state(token, &metachar);            // Update metachar state
        token = process_token(token, tokenlist, &heredoc_file, envp, &metachar);  // Process the token
        if (!token && heredoc_file)                         // Check for heredoc failure
        {
            free_tokenlist(tokenlist);
            return NULL;
        }
        create_and_link_token_node(tokenlist, token, metachar);   // Create and link token node
        token = get_next_token(NULL);                            // Get the next token
    }
    return tokenlist;
}

// int	main()
// {
// 	t_tokenlist	*tokenlist;
// 	char	*input;

// 	input = strdup("cmd1 cmd2 >> cmd3 | cmd4");
// 	tokenlist = get_tokenlist(input);
// }
