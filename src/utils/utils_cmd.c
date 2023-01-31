/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 16:50:11 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/27 09:16:03 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	get_code_error(int info, int new_error_code)
{
	static int	error_code;

	if (info == 0)
		return (error_code);
	error_code = new_error_code;
	return (-1);
}

char	*get_cmd_lst_env(t_minishell **minishell, char *cmd, t_list *lst)
{
	t_env	*lst_env;
	char	**tmp_split;
	char	*path_to_cmd;

	if (cmd[0] == '\0')
		return (ft_strdup(cmd));
	while (lst)
	{
		lst_env = lst->content;
		if (ft_strncmp(lst_env->name, "PATH", 4) == 0)
		{
			tmp_split = ft_split(lst_env->value, ':');
			path_to_cmd = get_cmd(cmd, tmp_split);
			free_split(tmp_split);
			check_dir(minishell, path_to_cmd);
			return (path_to_cmd);
		}
		lst = lst->next;
	}
	check_dir(minishell, cmd);
	return (ft_strdup(cmd));
}

char	*get_cmd(char *cmd, char **path)
{
	char	*path_to_cmd;
	char	*tmp;
	int		i;
	int		check_execute;

	i = -1;
	check_execute = -1;
	while (path && path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		path_to_cmd = ft_strjoin(tmp, cmd);
		free(tmp);
		check_execute = access(path_to_cmd, X_OK);
		if (check_execute == 0)
			return (path_to_cmd);
		free(path_to_cmd);
	}
	return (ft_strdup(cmd));
}

void	initialize_minishell(char **env, t_minishell **minishell)
{
	get_code_error(1, 0);
	(*minishell)->func = NULL;
	(*minishell)->pid = NULL;
	dup_env(env, &(*minishell)->lst_env);
	(*minishell)->fd_input = -2;
	(*minishell)->fd_output = -2;
	(*minishell)->check_export = 1;
	g_global.func = NULL;
}
