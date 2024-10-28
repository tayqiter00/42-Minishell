/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execve_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 21:34:52 by xquah             #+#    #+#             */
/*   Updated: 2024/10/28 14:33:19 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmdlist(t_tokenlist *currcmd)
{
	t_tokennode	*current;
	int			count;

	count = 0;
	current = currcmd->head;
	while (current)
	{
		current = current->next;
		count++;
	}
	return (count);
}
