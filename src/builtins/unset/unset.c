/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:40:23 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/27 16:04:31 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_unset(t_env *lst)
{
	free(lst->name);
	free(lst->value);
	free(lst);
}

void	cmd_unset(char **args, t_list **env)
{
	t_list	*lst;
	t_list	*tmp;
	t_env	*content;
	int		i;

	i = 0;
	lst = *env;
	while (args[++i])
	{
		while (*env)
		{
			content = (*env)->content;
			if (ft_strcmp(content->name, args[i]) == 0)
			{
				tmp->next = tmp->next->next;
				free_unset(content);
				free(*env);
				break ;
			}
			tmp = *env;
			*env = (*env)->next;
		}
		*env = lst;
	}
}
