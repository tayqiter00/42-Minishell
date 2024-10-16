/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xquah <xquah@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:14:40 by xquah             #+#    #+#             */
/*   Updated: 2024/10/16 17:49:11 by xquah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool	is_equal(char c)
{
	return (c == '=');
}

bool	is_uppercase(char c)
{
	return (c >= 'A' && c <= 'Z');
}

bool	is_lowercase(char c)
{
	return (c >= 'a' && c <= 'z');
}

bool is_sign(char c)
{
	return (c == '+' || c == '-');
}
