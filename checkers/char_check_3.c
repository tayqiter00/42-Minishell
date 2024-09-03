/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_check_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 11:18:14 by qtay              #+#    #+#             */
/*   Updated: 2024/09/02 23:46:55 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

bool    is_dollarsign(int c)
{
    return (c == '$');
}

bool    is_pipe(int c)
{
    return (c == '|');
}

/**
 * Prob only need space, \t and \n
 */
bool    is_whitespace(int c)
{
    return (c == ' '
        || c == '\t'
        || c == '\n'
        || c == '\v'
        || c == '\f'
        || c == '\r'); // check if should include newline
}

bool    is_newline(int c)
{
    return (c == '\n');
}
