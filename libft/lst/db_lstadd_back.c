/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 14:25:05 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/09 14:26:07 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	db_lstadd_back(t_db_list **lst, t_db_list *new)
{
	t_db_list	*tmp;

	if (!(*lst))
		*lst = new;
	else
	{
		tmp = db_lstlast(*lst);
		db_lstlast(*lst)->next = new;
		new->next = NULL;
		new->prev = tmp;
	}
}
