/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 10:16:38 by mrudloff          #+#    #+#             */
/*   Updated: 2023/01/28 17:12:29 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	ft_perror(char *str)
{
	ft_fprintf(STDERR_FILENO, "saucishell: cd: ");
	perror(str);
}

static void	change_pwd(t_list **env)
{
	t_env	*actual_path;
	t_env	*old_path;

	actual_path = get_env("PWD", env);
	old_path = get_env("OLDPWD", env);
	if (!actual_path)
	{
		if (old_path && old_path->value)
		{
			free(old_path->value);
			old_path->value = NULL;
		}
		return ;
	}
	if (old_path)
	{
		free(old_path->value);
		old_path->value = ft_strdup(actual_path->value);
	}
	if (actual_path->value)
		free(actual_path->value);
	actual_path->value = getcwd(NULL, PATH_MAX);
}

void	cmd_cd(char **args, t_list **env)
{
	t_env	*home;

	if (args && args[1] && args[2])
		ft_fprintf(STDERR_FILENO, "saucishell: too many arguments\n");
	if (args && args[1] && args[2])
		get_code_error(1, 1);
	else if (!args[1] || !ft_strncmp(args[1], "~", 1))
	{
		home = get_env("HOME", env);
		if (!home)
		{
			ft_fprintf(STDERR_FILENO, "saucishell: cd: HOME not set\n");
			get_code_error(1, 1);
			return ;
		}
		chdir(home->value);
		change_pwd(env);
	}
	else if (chdir(args[1]) == -1)
	{
		get_code_error(1, 1);
		ft_perror(args[1]);
	}
	else
		change_pwd(env);
}
