/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:26:32 by qtay              #+#    #+#             */
/*   Updated: 2024/09/08 17:32:39 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/**
 * Format: export [name[=value]]
 * 
 * Mark each shell var [name] to be passed to child processes in the
 * enviroment.
 * 
 * If no names are supplied, a list of names of all exported variables is
 * displayed.
 * 
 * If a variable name is followed by =value, the value of the v
*/
