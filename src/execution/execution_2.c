/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:51:21 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/26 11:05:27 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_export(t_minishell **minishell)
{
	if (!(*minishell)->func->cmd[1])
		return (1);
	else if (((*minishell)->func->cmd[1] && (*minishell)->func->next) \
		|| (ft_strcmp((*minishell)->start_func->cmd[0], "export") == 0))
		return (0);
	return (1);
}

void	execution_2(t_minishell **minishell, char **env, int i)
{
	if ((*minishell)->func->check_execution != -1
		&& (*minishell)->func->cmd && (*minishell)->func->cmd[0][0] != '\0' \
		&& is_builtins_no_fork((*minishell)->func->cmd[0]) == 0)
		loop_function(minishell, env, i);
	else if ((*minishell)->func->cmd \
		&& is_builtins_no_fork((*minishell)->func->cmd[0]) == 1)
		execve_builtins_no_fork(minishell, (*minishell)->func->cmd);
	(*minishell)->func = (*minishell)->func->next;
}
