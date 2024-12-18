/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:14:40 by xquah             #+#    #+#             */
/*   Updated: 2024/10/28 22:30:58 by qtay             ###   ########.fr       */
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

bool	is_sign(char c)
{
	return (c == '+' || c == '-');
}
