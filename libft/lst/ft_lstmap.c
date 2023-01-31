/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 09:05:09 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/09 14:26:44 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*first;
	t_list		*prev;
	t_list		*current;

	if (!lst || !f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		current = ft_lstnew(lst->content);
		if (!current)
		{
			ft_lstclear(&first, del);
			return (NULL);
		}
		if (!first)
			first = current;
		else
			prev->next = current;
		current->content = f(current->content);
		prev = current;
		lst = lst->next;
	}
	return (first);
}
