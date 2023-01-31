/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_builtins.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 14:27:41 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 11:45:13 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	execve_builtins_no_fork_2(t_minishell **minishell, char **cmd)
{
	int		fd[2];

	if ((*minishell)->func->next && (*minishell)->func->next->fd_input < 0 \
		&& (*minishell)->check_export != 0 && check_export(minishell) == 1)
	{
		if (pipe(fd) == -1)
			perror("pipe");
		cmd_export(cmd, &(*minishell)->lst_env, fd[1]);
		(*minishell)->func->check_execution = -1;
		close(fd[1]);
		(*minishell)->func->next->fd_input = fd[0];
	}
	else if (ft_strcmp(cmd[0], "export") == 0 \
		&& (*minishell)->check_export != 0 && !(*minishell)->func->next)
	{
		cmd_export(cmd, &(*minishell)->lst_env, 1);
		(*minishell)->func->check_execution = -1;
	}
}

void	execve_builtins_no_fork(t_minishell **minishell, char **cmd)
{
	char	**split;

	if (ft_strcmp(cmd[0], "cd") == 0 && !(*minishell)->start_func->next)
	{
		cmd_cd(cmd, &(*minishell)->lst_env);
		(*minishell)->func->check_execution = -1;
	}
	else if (ft_strcmp(cmd[0], "exit") == 0 && !(*minishell)->start_func->next)
	{
		if (!cmd[1])
			exit(0);
		split = ft_strdup_split(cmd);
		run_exit(split, minishell);
	}
	else if (ft_strcmp(cmd[0], "unset") == 0)
	{
		(*minishell)->func->check_execution = -1;
		check_unset_arg(cmd);
		cmd_unset(cmd, &(*minishell)->lst_env);
	}
	execve_builtins_no_fork_2(minishell, cmd);
}

void	execve_builtins(t_minishell **minishell, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		cmd_echo(cmd);
	else if (ft_strcmp(cmd[0], "pwd") == 0)
		cmd_pwd();
	else if (ft_strcmp(cmd[0], "env") == 0)
	{
		if (!cmd[1])
			cmd_env(&(*minishell)->lst_env);
		else
			ft_fprintf(STDERR_FILENO, "saucishell: env: too many arguments\n");
	}
}

void	do_builtins(t_minishell **minishell)
{
	if ((*minishell)->func->fd_input >= 0)
		dup2((*minishell)->func->fd_input, 0);
	if ((*minishell)->func->fd_output >= 0)
		dup2((*minishell)->func->fd_output, 1);
	if ((*minishell)->func->fd_output >= 0)
		close((*minishell)->func->fd_output);
	if ((*minishell)->func->fd_input >= 0)
		close((*minishell)->func->fd_input);
	close((*minishell)->fd[1]);
	close((*minishell)->fd[0]);
	execve_builtins(minishell, (*minishell)->func->cmd);
	close_all_fd((*minishell)->start_func);
	free_func((*minishell)->start_func);
	(*minishell)->func = NULL;
	free_all(minishell);
	exit(0);
}

void	do_builtins_pipe(t_minishell **minishell)
{
	if ((*minishell)->func->fd_input >= 0)
		dup2((*minishell)->func->fd_input, 0);
	if ((*minishell)->func->fd_output >= 0)
		dup2((*minishell)->func->fd_output, 1);
	else
		dup2((*minishell)->fd[1], 1);
	if ((*minishell)->func->fd_output >= 0)
		close((*minishell)->func->fd_output);
	if ((*minishell)->func->fd_input >= 0)
		close((*minishell)->func->fd_input);
	close((*minishell)->fd[1]);
	close((*minishell)->fd[0]);
	execve_builtins(minishell, (*minishell)->func->cmd);
	close_all_fd((*minishell)->start_func);
	free_func((*minishell)->start_func);
	(*minishell)->func = NULL;
	free_all(minishell);
	exit(0);
}
