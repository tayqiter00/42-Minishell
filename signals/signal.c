/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 14:09:39 by qtay              #+#    #+#             */
/*   Updated: 2024/10/01 00:29:23 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * SIGINT (Ctrl+C) will re-prompt.
 * SIGQUIT (Ctrl+\) will do nothing.
 * EOF (Ctrl+D) will quit the shell if empty line. Else, do nothing.
 * 
 * When running child processes, parent has to ignore all signals and the
 * child has to return to the default signal. This means Ctrl+C WILL
 * interrupt the child instead of re-prompting.
 * 
 * After the child finishes executing, parent has to return to the shell-
 * specific signals (meaning SIGINT goes back to reprompting etc).
 */

void	default_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	ignore_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

static void	re_prompt(int signum)
{
		set_exit_status(130);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
}

void	config_signals(void)
{
	signal(SIGINT, re_prompt);
	signal(SIGQUIT, SIG_IGN);
}
