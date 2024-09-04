/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:19:30 by qtay              #+#    #+#             */
/*   Updated: 2024/09/04 16:17:36 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "sys_headers.h"
# include "../libft/libft.h"

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

char		*get_next_env(char *token);
char        *get_next_token(char *input);
t_tokenlist	*get_tokenlist(char *input, char **envp);
int			count_leading_chars(char *token, char *env);

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
bool    is_whitespace(int c);
bool    is_doublequote(int c);
bool    is_singlequote(int c);
bool    is_questionmark(int c);
bool    is_heredoc(char *token);
bool	is_metachar(char *token);

#endif
