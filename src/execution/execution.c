/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:26:59 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/29 10:24:40 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	do_function_2(t_minishell **mini, char **env)
{
	char	*cmd;
	int		exit_code;

	cmd = get_cmd_lst_env(mini, (*mini)->func->cmd[0], (*mini)->lst_env);
	if ((*mini)->func->fd_input > 0)
		dup2((*mini)->func->fd_input, 0);
	if ((*mini)->func->fd_output > 0)
		dup2((*mini)->func->fd_output, 1);
	else
		dup2((*mini)->fd[1], 1);
	if ((*mini)->func->fd_output > 0)
		close((*mini)->func->fd_output);
	if ((*mini)->func->fd_input > 0)
		close((*mini)->func->fd_input);
	close((*mini)->fd[1]);
	close((*mini)->fd[0]);
	close_all_fd((*mini)->start_func);
	execve(cmd, (*mini)->func->cmd, env);
	exit_code = print_error_code(cmd);
	free(cmd);
	close_all_fd((*mini)->start_func);
	free_func((*mini)->start_func);
	(*mini)->func = NULL;
	free_all(mini);
	exit(exit_code);
}

void	loop_function(t_minishell **minishell, char **env, int i)
{
	if (pipe((*minishell)->fd) < 0)
		perror("pipe");
	(*minishell)->pid[i] = fork();
	g_global.pid = (*minishell)->pid[i];
	if ((*minishell)->pid[i] < 0)
		perror("fork");
	if ((*minishell)->pid[i] == 0 \
		&& is_builtins((*minishell)->func->cmd[0]) == 0)
		do_function_2(minishell, env);
	else if ((*minishell)->pid[i] == 0)
		do_builtins_pipe(minishell);
	close((*minishell)->fd[1]);
	if ((*minishell)->func->next->fd_input < 2)
		(*minishell)->func->next->fd_input = (*minishell)->fd[0];
	else
		close((*minishell)->fd[0]);
}

static void	execute_last_function(t_minishell **mini, char **env)
{
	char	*cmd;
	int		exit_code;

	cmd = get_cmd_lst_env(mini, (*mini)->func->cmd[0], (*mini)->lst_env);
	if ((*mini)->func->fd_input > 0)
		dup2((*mini)->func->fd_input, 0);
	if ((*mini)->func->fd_output > 0)
		dup2((*mini)->func->fd_output, 1);
	if ((*mini)->func->fd_output > 0)
		close((*mini)->func->fd_output);
	if ((*mini)->func->fd_input > 0)
		close((*mini)->func->fd_input);
	close((*mini)->fd[1]);
	close((*mini)->fd[0]);
	close_all_fd((*mini)->start_func);
	execve(cmd, (*mini)->func->cmd, env);
	exit_code = print_error_code(cmd);
	free(cmd);
	close_all_fd((*mini)->start_func);
	free_func((*mini)->start_func);
	(*mini)->func = NULL;
	free_all(mini);
	exit(exit_code);
}

static void	last_pipe(t_minishell **minishell, char **env, int i)
{
	if (pipe((*minishell)->fd) < 0)
		perror("pipe");
	(*minishell)->pid[i] = fork();
	g_global.pid = (*minishell)->pid[i];
	if ((*minishell)->pid[i] < 0)
		perror("fork");
	if ((*minishell)->pid[i] == 0 \
		&& is_builtins((*minishell)->func->cmd[0]) == 0)
		execute_last_function(minishell, env);
	else if ((*minishell)->pid[i] == 0)
		do_builtins(minishell);
	close((*minishell)->fd[0]);
	close((*minishell)->fd[1]);
}

void	execution(t_minishell **mini, char **env)
{
	int			i;
	t_function	*tmp;

	i = 0;
	(*mini)->pid = get_tab_pid((*mini)->func);
	tmp = (*mini)->func;
	(*mini)->start_func = tmp;
	while ((*mini)->func)
	{
		if (!(*mini)->func->next)
			break ;
		execution_2(mini, env, i);
		i++;
	}
	if ((*mini)->func->check_execution != -1 && (*mini)->func->cmd \
		&& (!(*mini)->start_func->next || (*mini)->func->cmd[0][0] != '\0') \
		&& is_builtins_no_fork((*mini)->func->cmd[0]) == 0)
		last_pipe(mini, env, i);
	else if ((*mini)->func->check_execution != -1
		&& (*mini)->func->cmd)
		execve_builtins_no_fork(mini, (*mini)->func->cmd);
	close_all_fd(tmp);
	wait_fork_2(mini, i);
	free_func(tmp);
	(*mini)->func = NULL;
}
