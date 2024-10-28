/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:51:05 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 13:40:29 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_heredocs(t_tokenlist *tokenlist)
{
	int			count;
	t_tokennode	*current;

	count = 0;
	current = tokenlist->head;
	while (current)
	{
		if (is_heredoc(current->token) && is_metachar(current->token))
			count++;
		current = current->next;
	}
	return (count);	
}

int	eval_heredocs(t_tokenlist **tokenlist)
{
	int			count;
	int			heredocs_count;
	t_tokenlist	*result;

	if (!tokenlist || !(*tokenlist) || !(*tokenlist)->head)
		return (0);
	count = 1;
	heredocs_count = count_heredocs(*tokenlist);
	if (heredocs_count == 0 || heredocs_count == 1)
		return (heredocs_count);
	result = create_tokenlist();
	while ((*tokenlist)->head)
	{
		if (is_heredoc((*tokenlist)->head->token) && count != heredocs_count)
		{
			count++;
			free_tokennode(pop_tokennode(*tokenlist));
			free_tokennode(pop_tokennode(*tokenlist));
		}
		else
			link_tokenlist(pop_tokennode(*tokenlist), result);
	}
	free_tokenlist(*tokenlist);
	*tokenlist = result;
	return (heredocs_count);
}

void	unlink_heredocs(int heredoc_count)
{
	struct stat	st;
	char		*num;
	static int	count = 0;
	char		*heredoc_path;

	while (heredoc_count--)
	{
		num = ft_itoa(count);
		heredoc_path = ft_strjoin("./heredoc/minishell_temp_", num);
		free(num);
		if (stat(heredoc_path, &st) == 0)
		{
			unlink(heredoc_path);
			count++;
		}
		free(heredoc_path);
	}
}
void	read_terminal(char *delim, char **envp, int heredoc_fd)
{
	bool	has_quotes;
	char	*input;
	pid_t	pid;

	has_quotes = false;
	if (ft_strchr(delim, '"') || ft_strchr(delim, '\''))
		has_quotes = true;
	delim = sanitize_token(delim); // quote removals for actual delimiter
	pid = create_fork();
	if (pid == 0)
	{
		default_signals();
		while (get_exit_status() == 0) // maybe add sth related to global signal
		{
			input = readline("heredoc> ");
			if (!ft_strncmp(input, delim, ft_strlen(input)))
				break ;
			if (input == NULL && get_exit_status() == 0)
			{
				dprintf(STDERR_FILENO, "warning: here-document delimited by end-of-file\n"); // ft
				free(delim);
				return ;
			}
			if (!has_quotes)
				input = expand_env(input, envp);
			write(heredoc_fd, input, ft_strlen(input));
			write(heredoc_fd, "\n", 1);
			free(input);
		}
		exit(get_exit_status());
	}
	ignore_signals();
	wait_for_child();
	config_signals();
	free(delim);
	// free(input);
}

/**
 * Format for heredoc: [n]<<[-]delim (not gonna handle [n] and [-])
 * 
 * No expansions and substitutions should be performed on 'delim' (double
 * check if handled).
 * 
 * If 'delim' contains any quotes (incl. E\"OF), the delimiter is the result
 * of quote removal on 'delim', and the lines in the here-document are
 * NOT expanded.
 * 
 * Else, all lines are subjected to the usual expansion and substitution.
 * 
 * Quotes and backslashes aren't removed from the heredoc lines (not yet
 * handled).
 * 
 * cat << <</</> will throw syntax error
 */
char	*create_heredoc(char *delim, char **envp, bool metachar)
{
	char		*num;
	static int	count = 0;
	int			heredoc_fd;
	char		*path;
	
	if (metachar)
	{
		free(delim);
		dprintf(STDERR_FILENO, "syntax error near unexpected token\n"); // ft_dprintf
		return (NULL);
	}
	num = ft_itoa(count);
	path = ft_strjoin("./heredoc/minishell_temp_", num);
	free(num);
	heredoc_fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (heredoc_fd == -1)
	{
		dprintf(STDERR_FILENO, "open failed for heredoc_fd\n"); // ft_dprintf
		exit(OPEN_ERROR);
	}
	read_terminal(delim, envp, heredoc_fd);
	close(heredoc_fd); // right now the name of the temp file still persists so need to unlink() later
	count++;
	return (path);	
}



