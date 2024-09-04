/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:51:35 by qtay              #+#    #+#             */
/*   Updated: 2024/09/03 18:04:37 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	*errno_(void);

int	get_exit_status(void)
{
	return (*errno_());
}
void	set_exit_status(int status)
{
	*errno_() = status;
}

int	*errno_(void)
{
	static int	errnum = 0;

	return (&errnum);
}

// int	main()
// {
// 	printf("exit status is: %d\n", get_exit_status());
// 	set_exit_status(2);
// 	printf("exit status is: %d\n", get_exit_status());
// }
