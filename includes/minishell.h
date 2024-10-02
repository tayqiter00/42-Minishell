/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:19:30 by qtay              #+#    #+#             */
/*   Updated: 2024/10/02 15:56:02 by xquah            ###   ########.fr       */
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
char    	*read_inputline(void);
char		**dup_envp(char **envp);
int			count_num_env(char **envp);
void		free_double_arr(char **arr);
void    	set_in_quote(int c, bool *in_quote, int *quote_type);

/* ************************************************************************** */
/*                                TOKENIZATION                                */
/* ************************************************************************** */
t_tokenlist *create_tokenlist(void);
char		*get_next_env(char *token);
char        *get_next_token(char *input);
int			eval_heredocs(t_tokenlist **tokenlist);
t_tokenlist	*get_tokenlist(char *input, char **envp);
int			count_leading_chars(char *token, char *env);
t_tokennode *create_tokennode(char *token, bool metachar);
void		link_tokenlist(t_tokennode *tokennode, t_tokenlist *tokenlist);
void		free_tokenlist(t_tokenlist *tokenlist);
void		free_tokennode(t_tokennode *node);
t_tokennode	*pop_tokennode(t_tokenlist *tokenlist);
void		pop_extra_heredocs(t_tokenlist *tokenlist, int heredocs_count);
t_tokenlist	*find_first_non_heredoc(t_tokenlist *tokenlist);

/* ************************************************************************** */
/*                             SHELL EXPANSIONS                               */
/* ************************************************************************** */
char		*sanitize_token(char *token);
void		unlink_heredocs(int heredoc_count);
char		*expand_env(char *token, char **envp);
int			count_heredocs(t_tokenlist *tokenlist);
int			eval_heredocs(t_tokenlist **tokenlist);
char		*create_heredoc(char *delim, char **envp, bool metachar);
int			count_expanded_len(char *token, char **envp);
void		dup_sanitized_token(char *result, char *token);
void		dup_expanded_token(char *expanded_env, char *token, char **envp);

/* ************************************************************************** */
/*                                  BUILTINS                                  */
/* ************************************************************************** */
int			ft_pwd(void);
int			ft_echo(t_tokennode *args);
int			ft_cd(t_tokennode *args, char **envp);
int			ft_env(char **envp);
int			ft_exit();
int			ft_export(t_tokennode *args, char ***envp);
int			ft_unset(char **envp, t_tokennode *args);

/* ************************************************************************** */
/*                            BUILTINS UTILS                                  */
/* ************************************************************************** */

void		insert_valid_args(char ***envp, t_tokennode *args);
bool		is_not_duplicate(char **envp, char *args);
bool		entry_has_valid_name(char *args);

/* ************************************************************************** */
/*                          SIGNALS AND EXIT STATUSES                         */
/* ************************************************************************** */
void		config_signals(void);
int			get_exit_status(void);
void		set_exit_status(int status);
void		default_signals(void);
void		ignore_signals(void);

/* ************************************************************************** */
/*                                 EXECUTION                                  */
/* ************************************************************************** */
pid_t		create_fork(void);
void		eval_tokenlist(t_tokenlist *tokenlist, int heredoc_count, char ***envp);
int			exec_cmdlist(int prev_pipefd[], t_tokenlist **cmdlist, bool with_pipe, char ***envp);

/* ************************************************************************** */
/*                              I/O REDIRECTIONS                              */
/* ************************************************************************** */
void		close_pipes(int prev_pipefd[]);
void		store_oristdio(int ori_stdio[]);
void		restore_oristdio(int ori_stdio[]);
t_tokenlist	*extract_redirs(t_tokenlist **cmdlist);
void		store_pipefd(int pipefd[], int prev_pipefd[]);
void		set_normcmd_redir(int infilefd, int outfilefd);
void		read_from_pipe(int prev_pipefd[], int infilefd);
int			get_redirfds(int redir_fds[], t_tokenlist **cmdlist);
void		child_redir(int pipefd[], int prev_pipefd[], int redir_fds[]);

/* ************************************************************************** */
/*                              WORD/CHAR CHECKS                              */
/* ************************************************************************** */
bool    is_pipe(int c);
bool    is_blank(int c);
bool    is_quote(int c);
bool    is_newline(int c);
bool    is_backslash(int c);
bool    is_dollarsign(int c);
bool	is_underscore(int c);
bool    is_doublequote(int c);
bool    is_singlequote(int c);
bool	is_redir(char *token);
bool    is_questionmark(int c);
bool    is_append(char *token);
bool    is_infile(char *token);
bool    is_outfile(char *token);
bool    is_heredoc(char *token);
bool	is_metachar(char *token);
bool	is_ampersand(char c);
bool	is_exclamation(char c);
bool	is_question_mark(char c);
bool	is_builtin(t_tokenlist *cmdlist);
bool	is_valid_env_name(char c);
bool	is_equal(char c);
bool	is_uppercase(char c);
bool	is_lowercase(char c);
bool	is_special_env_name(char c);

#endif
