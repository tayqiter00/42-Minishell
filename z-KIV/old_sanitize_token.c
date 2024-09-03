// bool	is_escapable(int c)
// {
// 	return (c == '$'
// 		|| c == '\n'
// 		|| c == '"'
// 		|| c == '\\');
// }

// /**
//  * The outer most quotes that aren't escaped should be removed
//  */
// void	dup_sanitized_token(char *result, t_tokennode *node)
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
// 	start = result;
// 	while (*token)
// 	{
// 		if (is_backslash(*token) && !should_escape && (!is_quote(quote_type)
// 			|| (is_doublequote(quote_type) && is_escapable(*(token + 1)))))
// 			should_escape = true;
// 		else if (!should_escape && is_singlequote(*token) && quote_type != '"')
// 			set_in_quote(*token, &in_quote, &quote_type);
// 		else if (!should_escape && is_doublequote(*token) && quote_type != '\'')
// 			set_in_quote(*token, &in_quote, &quote_type);
// 		else
// 		{
// 			*result = *token;
// 			result++;
// 			should_escape = false;
// 		}
// 		token++;
// 	}
// 	free(node->token);
// 	node->token = start;
// }

// /**
//  * Again, breaking this out to be used for heredoc
//  */
// void	sanitize_token(t_tokennode *node)
// {
// 	char	*result;

// 	result = calloc(ft_strlen(node->token) + 1, sizeof(char));
// 	if (!result)
// 	{
// 		dprintf(STDERR_FILENO, "malloc failed for removed quotes\n"); // ft_dprintf()
// 	}
// 	dup_sanitized_token(result, node);
// }
// /**
//  * echo "\'" should give \' but echo "\"" should give "
//  * Don't sanitize if it's heredoc's node which comes after << (not yet handled)
//  */
// void	sanitize_token_list(t_tokenlist *tokenlist)
// {
// 	t_tokennode	*node;
// 	bool		heredoc_node;
// 	// char		*result;
	
// 	heredoc_node = false;
// 	if (!tokenlist)
// 		return ;
// 	node = tokenlist->head;
// 	while (node)
// 	{
// 		// result = calloc(ft_strlen(node->token) + 1, sizeof(char));
// 		// if (!result)
// 		// {
// 		// 	dprintf(STDERR_FILENO, "malloc failed for removed quotes\n"); // ft_dprintf()
// 		// }
// 		// dup_sanitized_token(result, node);
// 		sanitize_token(node);
// 		node = node->next;
// 	}
// }