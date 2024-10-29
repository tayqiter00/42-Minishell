/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 19:57:43 by xquah             #+#    #+#             */
/*   Updated: 2024/10/28 22:03:33 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	contain_only_digits(char *first_arg)
{
	int	digits_len;

	first_arg += ft_strspn(first_arg, " ");
	if (is_sign(*first_arg))
		first_arg++;
	if (*first_arg == '\0')
		return (false);
	digits_len = ft_strspn(first_arg, "0123456789 ");
	return (digits_len == (int)ft_strlen(first_arg));
}

int	normalize_exit_code(char *first_arg)
{
	int	value;

	value = ft_atoi(first_arg);
	if (value > 0)
		return (value % 256);
	return ((value + 256) % 256);
}

void	handle_numeric_exit(char *first_arg, char *dup_subtoken)
{
	int	exit_code;

	exit_code = normalize_exit_code(first_arg);
	free(dup_subtoken);
	exit(exit_code);
}

/**
 * My bash says exit code for this is 2
 */
void	handle_non_numeric_exit(char *dup_subtoken)
{
	ft_dprintf(STDERR_FILENO, "numeric argument required\n");
	free(dup_subtoken);
	exit(2);
}
