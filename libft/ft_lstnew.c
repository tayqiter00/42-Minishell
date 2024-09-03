/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qtay <qtay@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 11:39:50 by qtay              #+#    #+#             */
/*   Updated: 2024/03/04 11:53:28 by qtay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*rtn;

	rtn = (t_list *)malloc(sizeof(t_list));
	if (!rtn)
		return (rtn = NULL);
	rtn->content = content;
	rtn->next = NULL;
	return (rtn);
}
/*
int	main(void)
{
	char	c = 'A';
	t_list	*new_node;

	new_node = ft_lstnew(&c);
	if (new_node != NULL)
    {
		printf("Content of the new node: %c\n", *((char *)new_node->content));
		free(new_node);
    }
    else
    {
		printf("Failed to create a new node.\n");
    }
	return 0;
}*/
