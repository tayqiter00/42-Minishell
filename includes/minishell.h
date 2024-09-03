/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:19:30 by qtay              #+#    #+#             */
/*   Updated: 2024/09/02 14:30:59 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "token.h"
# include "../libft/libft.h"
# include "sys_headers.h"

/* ************************************************************************** */
/*                              CHARACTER CHECKS                              */
/* ************************************************************************** */
bool    is_questionmark(int c);
bool    is_forwardslash(int c);
bool    is_singlequote(int c);
bool    is_doublequote(int c);
bool    is_quote(int c);
bool    is_dollarsign(int c);
bool    is_pipe(int c);
bool    is_space(int c);
bool    is_newline(int c);
bool    is_backslash(int c);
bool    is_whitespace(int c);
bool	is_underscore(int c);
bool    is_heredoc(char *token);
bool	is_metachar(char *token);

void    set_in_quote(int c, bool *in_quote, int *quote_type);

/* ************************************************************************** */
/*                                DOUBLE ARRAY                                */
/* ************************************************************************** */

void    free_double_array(char **double_array);

/* ************************************************************************** */
/*                               INPUT PARSING                                */
/* ************************************************************************** */

char    *read_inputline(void);

/* ************************************************************************** */
/*                              LEXICAL ANALYSIS                              */
/* ************************************************************************** */

t_tokenlist	*get_tokenlist(char *input, char **envp);
char        *get_next_token(char *input);

char	*get_next_env(char *token);
int		count_leading_chars(char *token, char *env);
void	expand_list_env(t_tokenlist *tokenlist, char **envp);
// void	expand_env(t_tokennode *tokennode, char **envp);
char	*expand_env(char *token, char **envp);
int		count_expanded_len(char *token, char **envp);
// void	dup_expanded_token(char *expanded_env, t_tokennode *node, char **envp);
void	dup_expanded_token(char *expanded_env, char *token, char **envp);
// void	sanitize_token_list(t_tokenlist *tokenlist);
char	*sanitize_token(char *token);
void	dup_sanitized_token(char *result, char *token);
char	*create_heredoc(char *delim, char **envp);

int	ft_echo(t_tokennode *args);
int	ft_pwd(void);

#endif
