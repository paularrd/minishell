/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 09:32:22 by mrudloff          #+#    #+#             */
/*   Updated: 2023/01/27 16:04:14 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	add_to_tab(char	**tab,	t_env *content)
{
	char	*tmp;

	tmp = ft_strdup(content->name);
	if (content->value)
	{
		*tab = ft_strjoin(tmp, "=\"");
		free(tmp);
		tmp = ft_strjoin(*tab, content->value);
		free(*tab);
		*tab = ft_strjoin(tmp, "\"");
		free(tmp);
		return ;
	}
	*tab = tmp;
}

char	**ft_lsttotab_str(t_list *lst)
{
	char	**tab;
	int		i;
	t_env	*content;

	i = ft_lstsize(lst);
	tab = malloc((i + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (lst)
	{
		content = lst->content;
		if (content->name[0] == '_' && !content->name[1])
			lst = lst->next;
		if (content->name[0] == '_' && !content->name[1])
			continue ;
		add_to_tab(&tab[i], content);
		lst = lst->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
