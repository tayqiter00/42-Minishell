/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:35:52 by qtay              #+#    #+#             */
/*   Updated: 2024/10/29 10:16:11 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

# ifndef WHITESPACE
#  define WHITESPACE " \t\n\v\f\r"
# endif

# include <stdbool.h>

typedef struct s_tokennode
{
	char				*token;
	bool				is_meta_char;
	struct s_tokennode	*next;
}	t_tokennode;

typedef struct s_tokenlist
{
	t_tokennode	*head;
}	t_tokenlist;

#endif
