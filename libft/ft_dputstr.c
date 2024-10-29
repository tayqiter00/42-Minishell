/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dputstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 14:27:25 by qtay              #+#    #+#             */
/*   Updated: 2024/10/28 22:59:12 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_dputstr(int fd, char *s)
{
	int	i;
	int	count;

	count = 0;
	if (!s)
		return (ft_dputstr(fd, "(null)"));
	i = -1;
	while (s[++i])
	{
		ft_dputchar(s[i], fd);
		count++;
	}
	return (count);
}
