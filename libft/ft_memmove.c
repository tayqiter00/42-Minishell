/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 20:18:42 by qtay              #+#    #+#             */
/*   Updated: 2024/02/25 15:42:21 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*p_dst;
	unsigned char	*p_src;
	size_t			i;

	if (!dst && !src)
		return (0);
	p_dst = (unsigned char *)dst;
	p_src = (unsigned char *)src;
	if (src > dst)
	{
		i = 0;
		while (i < len)
		{
			p_dst[i] = p_src[i];
			i++;
		}
	}
	else if (src < dst)
	{
		while (len-- > 0)
			p_dst[len] = p_src[len];
	}
	return (dst);
}
