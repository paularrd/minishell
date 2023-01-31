/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:01:19 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/27 16:37:17 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

pid_t	*get_tab_pid(t_function *func)
{
	int			i;
	pid_t		*tab_pid;
	t_function	*tmp;

	i = 0;
	tmp = func;
	while (func->next)
	{
		func = func->next;
		i++;
	}
	tab_pid = malloc((i + 1) * sizeof(pid_t));
	if (!tab_pid)
		return (NULL);
	i = 0;
	func = tmp;
	while (func->next)
	{
		tab_pid[i] = -1;
		func = func->next;
		i++;
	}
	tab_pid[i] = -1;
	return (tab_pid);
}

void	wait_fork_2(t_minishell **minishell, int i)
{
	int	y;
	int	status;

	y = 0;
	status = -1;
	while (y <= i)
	{
		if ((*minishell)->func->cmd)
			if ((*minishell)->func->check_execution != -1)
				if ((*minishell)->pid[y] != -1)
					waitpid((*minishell)->pid[y], &status, 0);
		y++;
	}
	free((*minishell)->pid);
	(*minishell)->pid = NULL;
	if (status != -1)
		get_code_error(1, WEXITSTATUS(status));
	g_global.check_execution_here = 1;
	(*minishell)->fd_input = -2;
}

int	is_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	return (0);
}

int	is_builtins_no_fork(char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	return (0);
}

int	print_error_code(char *cmd)
{
	if (errno == EACCES)
	{
		ft_fprintf(STDERR_FILENO, "saucishell: %s: Permission denied\n", cmd);
		return (126);
	}
	else
		ft_fprintf(STDERR_FILENO, "saucishell: %s: command not found\n", cmd);
	return (127);
	close(0);
	close(1);
	close(2);
}
