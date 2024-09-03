/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strspn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:13:00 by qtay              #+#    #+#             */
/*   Updated: 2024/08/27 15:13:23 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strspn(const char *str, const char *accept)
{
	int	len;

	if (!str || !accept)
		return (0);
	len = 0;
	while (str[len] && ft_strchr(accept, str[len]))
		len++;
	return (len);
}
