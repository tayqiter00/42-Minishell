/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 23:36:50 by xquah             #+#    #+#             */
/*   Updated: 2024/10/27 21:52:16 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	count_exit_args(t_tokennode *args)
{
	int		args_count;
	char	*dup_subtoken;
	char	*subtoken;

	args_count = 0;
	while (args)
	{
		dup_subtoken = ft_strdup(args->token);
		subtoken = ft_strtok(dup_subtoken, ' ');
		while (subtoken)
		{
			args_count++;
			subtoken = ft_strtok(NULL, ' ');
		}
		free(dup_subtoken);
		args = args->next;
	}
	return (args_count);
}

static int process_exit_args(t_tokennode *args)
{
	int args_count;
	char *dup_subtoken;
	char *first_arg;

	args_count = count_exit_args(args);
	dup_subtoken = ft_strdup(args->token);
	first_arg = ft_strtok(dup_subtoken, ' ');
	if (first_arg && contain_only_digits(first_arg))
	{
		if (args_count == 1)
			handle_numeric_exit(first_arg, dup_subtoken);
		printf("too many arguments\n");
	}
	else
		handle_non_numeric_exit(dup_subtoken);
	free(dup_subtoken);
	return (1);
}

/**
 * added ft_exit(), in case more things needs to be checked in the function other than just exit()
 *
*/
int	ft_exit(t_tokennode *args)
{
	if (args == NULL || count_exit_args(args) == 0)
		exit(0);
	return (process_exit_args(args));
}