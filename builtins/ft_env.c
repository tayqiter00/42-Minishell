/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:18:23 by qtay              #+#    #+#             */
/*   Updated: 2024/10/08 23:08:36 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Might wanna see if we wanna handle $? here
 * 
 * Check that [char **envp] gives the same thing as env
 * line 25 - checks that the current row isn't a placehodler for a variable that is freed (null character '\0') 
 */
int	ft_env(char **envp)
{
	while (*envp)
	{
		if (**envp != '\0')
			printf("%s\n", *envp);
		*envp++;
	}
	return (0);
}
