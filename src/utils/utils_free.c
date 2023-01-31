/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:48:08 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 11:23:52 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_all_fd(t_function *tmp)
{
	while (tmp)
	{
		if (tmp->fd_input >= 0)
			close(tmp->fd_input);
		if (tmp->fd_output >= 0)
			close(tmp->fd_output);
		tmp = tmp->next;
	}
}

void	free_lst_env(t_list *lst_env)
{
	t_list		*tmp;
	t_env		*tmp2;

	while (lst_env)
	{
		tmp2 = lst_env->content;
		free(tmp2->name);
		free(tmp2->value);
		free(tmp2);
		tmp = lst_env;
		lst_env = lst_env->next;
		free(tmp);
	}
	lst_env = NULL;
}

void	free_func(t_function *func)
{
	t_function	*tmp;

	while (func)
	{
		free_split(func->cmd);
		func->cmd = NULL;
		tmp = func;
		func = func->next;
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
}

void	free_all(t_minishell **minishell)
{
	free_lst_env((*minishell)->lst_env);
	if ((*minishell)->func)
	{
		close_all_fd((*minishell)->func);
		free_func((*minishell)->func);
	}
	(*minishell)->func = NULL;
	if ((*minishell)->pid)
		free((*minishell)->pid);
	free((*minishell));
	close(0);
	close(1);
	close(2);
}
