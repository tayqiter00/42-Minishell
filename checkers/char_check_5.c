/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 01:37:25 by xquah             #+#    #+#             */
/*   Updated: 2024/10/16 17:49:18 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_number(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_hash(char c)
{
	return (c == '#');
}

bool	is_asterisk(char c)
{
	return (c == '*');
}

bool	is_valid_env_name(char c)
{
	return (is_underscore(c)
		|| (is_uppercase(c))
		|| (is_lowercase(c))
		|| (is_number(c)));
}

bool	is_special_env_name(char c)
{
	return (is_number(c)
		|| (is_hash(c))
		|| (is_asterisk(c))
		|| (is_ampersand(c))
		|| (is_dollarsign(c))
		|| (is_exclamation(c))
		|| (is_question_mark(c)));
}
