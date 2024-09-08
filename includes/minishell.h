/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:19:30 by qtay              #+#    #+#             */
/*   Updated: 2024/09/08 09:31:23 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "sys_headers.h"
# include "../libft/libft.h"

# define R_END 0
# define W_END 1
# define SYNTAX_ERROR 2
# define MALLOC_ERROR 3
# define OPEN_ERROR 4

/* ************************************************************************** */
/*                               INPUT PARSING                                */
/* ************************************************************************** */
char    *read_inputline(void);
char	**dup_envp(char **envp);
void	free_double_arr(char **arr);
void    set_in_quote(int c, bool *in_quote, int *quote_type);

/* ************************************************************************** */
/*                                TOKENIZATION                                */
/* ************************************************************************** */
t_tokenlist *create_tokenlist(void);
char		*get_next_env(char *token);
char        *get_next_token(char *input);
t_tokenlist	*get_tokenlist(char *input, char **envp);
int			count_leading_chars(char *token, char *env);
t_tokennode *create_tokennode(char *token, bool metachar);
void		link_tokenlist(t_tokennode *tokennode, t_tokenlist *tokenlist);

/* ************************************************************************** */
/*                             SHELL EXPANSIONS                               */
/* ************************************************************************** */
char	*sanitize_token(char *token);
char	*expand_env(char *token, char **envp);
char	*create_heredoc(char *delim, char **envp);
int		count_expanded_len(char *token, char **envp);
void	dup_sanitized_token(char *result, char *token);
void	dup_expanded_token(char *expanded_env, char *token, char **envp);

/* ************************************************************************** */
/*                                  BUILTINS                                  */
/* ************************************************************************** */
int	ft_pwd(void);
int	ft_echo(t_tokennode *args);
int	ft_cd(t_tokennode *args, char **envp);

/* ************************************************************************** */
/*                          SIGNALS AND EXIT STATUSES                         */
/* ************************************************************************** */
void	config_signals(void);
int		get_exit_status(void);
void	set_exit_status(int status);

/* ************************************************************************** */
/*                              WORD/CHAR CHECKS                              */
/* ************************************************************************** */
bool    is_pipe(int c);
bool    is_quote(int c);
bool    is_newline(int c);
bool    is_backslash(int c);
bool    is_dollarsign(int c);
bool	is_underscore(int c);
bool    is_blank(int c);
bool    is_doublequote(int c);
bool    is_singlequote(int c);
bool    is_questionmark(int c);
bool    is_heredoc(char *token);
bool	is_metachar(char *token);
bool	is_redir(char *token);
bool    is_outfile(char *token);
bool    is_append(char *token);
bool    is_infile(char *token);

void	free_tokenlist(t_tokenlist *tokenlist);
t_tokennode	*pop_tokennode(t_tokenlist *tokenlist);
void	eval_tokenlist(t_tokenlist *tokenlist);
void	exec_cmdlist(t_tokenlist **cmdlist, bool with_pipe);
void	free_tokennode(t_tokennode *node);
int	get_redirfds(int redir_fds[2], t_tokenlist **cmdlist);

#endif
