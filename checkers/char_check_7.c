/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:32:43 by xquah             #+#    #+#             */
/*   Updated: 2024/10/16 17:41:47 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	has_alpha(char *str)
{
	while (*str)
	{
		if (ft_isalpha(*str))
			return (true);
		str++;
	}
	return (false);
}

bool	is_invalid_filename(char *bin)
{
	return (*bin == '\0' || !ft_strcmp(bin, ".") || !ft_strcmp(bin, "..") \
		|| !ft_strcmp(bin, "/") || !has_alpha(bin));
}
