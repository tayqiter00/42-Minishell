/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:18:23 by qtay              #+#    #+#             */
/*   Updated: 2024/09/21 23:35:01 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Might wanna see if we wanna handle $? here
 * 
 * Check that [char **envp] gives the same thing as env
 */
int	ft_env(char **envp)
{
	while (*envp)
	{
		printf("%s\n", *envp);
		*envp++;
	}
	return (0);
}
