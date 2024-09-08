/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:18:09 by qtay              #+#    #+#             */
/*   Updated: 2024/09/06 06:25:59 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    is_singlequote(int c)
{
    return (c == '\'');
}

bool    is_doublequote(int c)
{
    return (c == '\"');
}

bool    is_quote(int c)
{
    return (is_singlequote(c) || is_doublequote(c));
}

bool    is_infile(char *token)
{
	return (!ft_strncmp(token, "<", 1));	
}