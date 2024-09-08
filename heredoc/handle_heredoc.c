/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 15:51:05 by qtay              #+#    #+#             */
/*   Updated: 2024/09/06 17:29:44 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// #include <errno.h>
// extern int    errno;

void	read_terminal(char *delim, char **envp, int heredoc_fd)
{
	bool	has_quotes;
	char	*input;

	has_quotes = false;
	if (ft_strchr(delim, '"') || ft_strchr(delim, '\''))
		has_quotes = true;
	delim = sanitize_token(delim); // quote removals for actual delimiter
	// delim = ft_strjoin(delim, "\n"); // exit for malloc failure instead of return NULL
	input = readline("heredoc> "); // technically should check for readline malloc...
	if (input == NULL)
	{
		dprintf(STDERR_FILENO, "warning: here-document delimited by end-of-file\n"); // ft
		free(delim);
		return ;
	}
	while (get_exit_status() == 0) // maybe add sth related to global signal
	{
		if (!ft_strncmp(input, delim, ft_strlen(input)))
			break ;
		if (!has_quotes)
			input = expand_env(input, envp);
		write(heredoc_fd, input, ft_strlen(input));
		write(heredoc_fd, "\n", 1);
		free(input);
		input = readline("heredoc> ");
	}
	free(delim);
	free(input);
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
char	*create_heredoc(char *delim, char **envp)
{
	int		heredoc_fd;
	char	*name;
	
	name = "minishell_temp.txt";
	heredoc_fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (heredoc_fd == -1)
	{
		dprintf(STDERR_FILENO, "open failed for heredoc_fd\n"); // ft_dprintf
		exit(OPEN_ERROR);
	}
	read_terminal(delim, envp, heredoc_fd);
	close(heredoc_fd); // right now the name of the temp file still persists so need to unlink() later
	return (ft_strdup(name));	
}



