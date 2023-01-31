/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 17:33:56 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/26 17:51:13 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
// get_prompt get all information for prompt in bash
// NOT FINISH, leaks and errors in some cases
*/
char	*get_prompt(void)
{
	char	*prompt;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = get_pwd();
	tmp3 = ft_strjoin("\e[1;36m", tmp);
	tmp2 = ft_strjoin("\e[1;32m➜  \033[0;37m", tmp3);
	free(tmp);
	free(tmp3);
	prompt = ft_strjoin(tmp2, ": \x1B[0m");
	free(tmp2);
	return (prompt);
}

int	get_size(char *pwd)
{
	int		i;
	int		y;

	i = 0;
	while (pwd[i])
	{
		y = 0;
		if (pwd[i] == '/')
		{
			i++;
			while (pwd[i] != '/' && pwd[i])
			{
				y++;
				i++;
			}
		}
		if (pwd[i] == '\0')
			break ;
		if (pwd[i] != '/')
			i++;
	}
	return (y);
}

static char	*get_last_path(char *pwd)
{
	int		i;
	int		y;
	char	*last_path;

	i = ft_strlen(pwd);
	y = get_size(pwd);
	last_path = malloc((y + 1) * sizeof(char));
	if (!last_path)
		return (NULL);
	i -= y;
	y = 0;
	while (pwd[i])
	{
		last_path[y] = pwd[i];
		y++;
		i++;
	}
	last_path[y] = '\0';
	free(pwd);
	return (last_path);
}

char	*get_pwd(void)
{
	char	*pwd;

	pwd = malloc(1024 * sizeof(char));
	if (!pwd)
		return (NULL);
	pwd = getcwd(pwd, 1024);
	pwd = get_last_path(pwd);
	return (pwd);
}

void	check_dir(t_minishell **minishell, char *cmd)
{
	DIR		*dir;

	dir = opendir(cmd);
	if (!dir)
		return ;
	closedir(dir);
	ft_fprintf(2, "saucishell: %s: Is a directory\n", cmd);
	close((*minishell)->fd[0]);
	close((*minishell)->fd[1]);
	free(cmd);
	free((*minishell)->pid);
	close_all_fd((*minishell)->start_func);
	free_lst_env((*minishell)->lst_env);
	free_func((*minishell)->start_func);
	(*minishell)->func = NULL;
	free(*minishell);
	exit(126);
}
