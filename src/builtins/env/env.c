/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 15:05:52 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/27 08:22:28 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	dup_env(char **env, t_list **lst_env)
{
	int		i;
	t_env	*content;

	*lst_env = NULL;
	i = -1;
	while (env[++i])
		ft_lstadd_back(lst_env, ft_lstnew(create_new_env(env[i])));
	content = create_new_env("_=]");
	modify_env(content, lst_env);
}

void	cmd_env(t_list **env)
{
	t_list	*lst;
	t_env	*tmp;

	lst = *env;
	while (*env)
	{
		tmp = (*env)->content;
		if (tmp->value)
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		*env = (*env)->next;
	}
	*env = lst;
}

/*	 This function modifies an environnement variable
 *	--------------------------------------------------
 *	t_env new: In this structure you must add the name
 *	of the env to be modified and the associated value
 *	In the function that calls it.Don't forget to free
 *	the whole structure.
 */
void	modify_env(t_env *new, t_list **env)
{
	t_list	*lst;
	t_env	*content;

	lst = *env;
	while (lst)
	{
		content = lst->content;
		if (ft_strcmp(new->name, content->name) == 0)
		{
			free(content->name);
			if (content->value)
				free(content->value);
			free(content);
			content = malloc(sizeof(t_env));
			content->name = ft_strdup(new->name);
			free(new->name);
			content->value = ft_strdup(new->value);
			free(new->value);
			free(new);
			new = NULL;
			lst->content = content;
			break ;
		}
		lst = lst->next;
	}
}

/*       This function is used to retrieve an env
 * ---------------------------------------------------
 * STR: is the name of the variable we want to retrive
 * It returns a structure of type t_env if the variable
 * has been found. And NULL in the other case
 */

void	*get_env(char *str, t_list **env)
{
	t_list	*lst;
	t_env	*content;

	content = NULL;
	lst = *env;
	while ((*env))
	{
		content = (*env)->content;
		if (ft_strcmp(str, content->name) == 0)
		{
			*env = lst;
			return (content);
		}
		(*env) = (*env)->next;
	}
	*env = lst;
	return (NULL);
}
