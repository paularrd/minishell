/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 15:56:07 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/09 14:26:15 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	db_lstclear(t_db_list **lst)
{
	t_db_list		*tmp;

	if (*lst)
	{
		while ((*lst)->prev != NULL)
			*lst = (*lst)->prev;
		while (*lst)
		{
			tmp = (*lst)->next;
			free(*lst);
			(*lst) = tmp;
		}
		*lst = NULL;
	}
}
