/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:35:52 by qtay              #+#    #+#             */
/*   Updated: 2024/08/30 17:32:56 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#ifndef TOKEN_H
# define TOKEN_H

# define WHITESPACE " \t\n\v\f\r"

typedef struct s_tokennode
{
    char                *token;
	bool				is_meta_char;
    struct s_tokennode   *next;
}   t_tokennode;

typedef struct s_tokenlist
{
    t_tokennode *head;
}   t_tokenlist;

#endif
