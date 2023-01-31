/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:31:58 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 16:57:08 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_swap(char **a, char **b)
{
	char	*c;

	c = *a;
	*a = *b;
	*b = c;
}

static void	ft_sort_str_tab(char **tab)
{
	int	i;
	int	j;
	int	size;

	size = 0;
	if (!tab)
		return ;
	while (tab[size])
		size++;
	if (size == 0)
		return ;
	i = 0;
	while (i < size - 1)
	{
		j = i + 1;
		while (j < size)
		{
			if (ft_strcmp_2(tab[i], tab[j]) > 0)
				ft_swap(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
}

static t_list	*create_new_node(t_env *new)
{
	t_list	*new_lst;

	new_lst = malloc(sizeof(t_list));
	new_lst->content = new;
	new_lst->next = NULL;
	return (new_lst);
}

void	cmd_export(char **args, t_list **lst_env, int fd)
{
	char	**env;
	int		i;

	i = 0;
	if (!args[1])
	{
		env = ft_lsttotab_str((*lst_env));
		ft_sort_str_tab(env);
		while (env[i])
		{
			ft_fprintf(fd, "declare -x %s\n", env[i]);
			i++;
		}
		free_split(env);
	}
	else
	{
		i = 0;
		while (args[++i])
			add_export(lst_env, args[i]);
	}
}

void	add_export(t_list **env, char *var)
{
	int		i;
	t_list	*lst;
	t_env	*tmp;
	t_env	*content;

	i = 0;
	content = NULL;
	lst = *env;
	tmp = create_new_env(var);
	if (!tmp)
		return ;
	while ((*env))
	{
		content = (*env)->content;
		if (ft_strcmp(content->name, tmp->name) == 0)
		{
			modify_env(tmp, env);
			break ;
		}
		(*env) = (*env)->next;
	}
	if (!(*env))
		ft_lstadd_back(&lst, create_new_node(tmp));
	(*env) = lst;
}
