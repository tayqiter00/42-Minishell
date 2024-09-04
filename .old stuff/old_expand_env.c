/**
 * I'm not sure why freeing node->token here results in invalid pointer... to 
 * come back later. But not freeing here gives me "possible leaks"
 */
// void	dup_expanded_token(char *expanded_env, t_tokennode *node, char **envp)
// {
// 	char	*env;
// 	char	*token;
	
// 	token = node->token;
// 	env = get_next_env(node->token);
// 	while (env)
// 	{
// 		dup_leading_chars(expanded_env, node->token, env);
// 		dup_env_value(expanded_env, env, envp);
// 		node->token += count_leading_chars(node->token, env) + ft_strlen(env);
// 		free(env);
// 		env = get_next_env(NULL);
// 	}
// 	free(env);
// 	// free(node->token); // apparently no need to free?
// 	if (*expanded_env)
// 	{
// 		node->token = expanded_env;
// 	}
// 	else
// 		free(expanded_env);
// }

/**
 * Broke this out from expand_list_env to be used for heredoc expansion
 */
// void	expand_env(t_tokennode *node, char **envp)
// {
// 	int		expanded_len;
// 	char	*expanded_env;

// 	expanded_len = count_expanded_len(node->token, envp);
// 	expanded_env = calloc((expanded_len + 1), sizeof(char)); // ft_calloc()
// 	if (!expanded_env)
// 	{
// 		dprintf(STDERR_FILENO, "malloc failed for expanded env\n"); // ft_dprintf(), free and exit
// 	}
// 	dup_expanded_token(expanded_env, node, envp); // gotta free original token
// }

/**
 * Should take into account multiple $ in a single subtok
 * Should return empty string if env not found
 * Don't need to expand if it comes immediately after heredoc (not yet handled)
 */
// void	expand_list_env(t_tokenlist *tokenlist, char **envp)
// {
// 	int			expanded_len;
// 	t_tokennode	*node;
// 	char		*expanded_env;
	
// 	if (!tokenlist)
// 		return ;
// 	node = tokenlist->head;
// 	while (node)
// 	{
// 		expand_env(node, envp);
// 		// expanded_len = count_expanded_len(node->token, envp);
// 		// expanded_env = calloc((expanded_len + 1), sizeof(char)); // ft_calloc()
// 		// if (!expanded_env)
// 		// {
// 		// 	dprintf(STDERR_FILENO, "malloc failed for expanded env\n"); // ft_dprintf(), free and exit
// 		// }
// 		// dup_expanded_token(expanded_env, node, envp); // gotta free original token
// 		node = node->next;
// 	}
// }