/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_remove_backslashes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 13:44:33 by qtay              #+#    #+#             */
/*   Updated: 2024/08/31 16:54:34 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../includes/minishell.h"

// bool	is_escapable(int c)
// {
// 	return (c == '$'
// 		|| c == '\n'
// 		|| c == '"'
// 		|| c == '\\');
// }

// void	dup_removed_backslashes(char *removed_backslashes, t_tokennode *node)
// {
// 	char	*token;
// 	char	*start;
// 	bool	in_quote;
// 	int		quote_type;
// 	bool	should_escape;

// 	token = node->token;
// 	in_quote = false;
// 	quote_type = '\0';
// 	should_escape = false;
// 	start = removed_backslashes;
// 	while (*token)
// 	{
// 		if (is_backslash(*token) && !should_escape && (!is_quote(quote_type)
// 			|| (is_doublequote(quote_type) && is_escapable(*(token + 1)))))
// 			should_escape = true;
// 		else if (!should_escape && is_quote(*token))
// 		{
// 			set_in_quote(*token, &in_quote, &quote_type);
// 			*removed_backslashes = *token; // can i do *removed_backslashes++ = *token;
// 			removed_backslashes++;
// 		}
// 		else
// 		{
// 			*removed_backslashes = *token;
// 			removed_backslashes++;
// 			should_escape = false;
// 		}
// 		token++;
// 	}
// 	free(node->token);
// 	node->token = start;
// }

// /**
//  * Non-quoted backslashes preserve the literal value of the next character
//  * that follows, except for newline (i.e., \\n will be treated as \n and
//  * removed by readline()) and will be removed.
//  * 
//  * Single quoted backslashes lose their ability as escape characters and will
//  * NOT be removed.
//  * 
//  * Double quoted backslashes lose their ability as escape characters and will
//  * NOT be removed unless the next character that follows is a $, ", \, ` or
//  * newline.
//  */
// void	remove_backslashes(t_tokenlist *tokenlist)
// {
// 	t_tokennode	*node;
// 	char		*removed_backslashes;

// 	if (!tokenlist)
// 		return ;
// 	node = tokenlist->head;
// 	while (node)
// 	{
// 		removed_backslashes = calloc(ft_strlen(node->token) + 1, sizeof(char)); // ft_calloc()
// 		if (!removed_backslashes)
// 		{
// 			dprintf(STDERR_FILENO, "malloc failed for removed backslashes\n"); // ft_dprintf()
// 		}
// 		dup_removed_backslashes(removed_backslashes, node);
// 		node = node->next;
// 	}
// }