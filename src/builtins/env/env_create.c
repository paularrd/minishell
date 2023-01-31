/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 11:32:15 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/27 16:07:37 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	print_error(char *str)
{
	write(STDERR_FILENO, "saucishell: export:`", 20);
	write(STDERR_FILENO, str, ft_strlen(str));
	write(STDERR_FILENO, "': not a valid identifier\n", 26);
	get_code_error(1, 1);
}

int	is_valid_name(char *str)
{
	int	i;

	i = 1;
	if (str && (ft_isalpha(str[0]) || str[0] == '_'))
	{
		while (str && str[i])
		{
			if (!ft_isalnum(str[i]) && str[i] != '_')
			{
				print_error(str);
				return (0);
			}
			i++;
		}
	}
	else
	{
		print_error(str);
		return (0);
	}
	return (1);
}

static void	set_new_env(char **split, t_env **env, int condition)
{
	int		i;
	char	*tmp;

	if (!(*env))
		return ;
	(*env)->value = NULL;
	(*env)->name = ft_strdup(split[0]);
	i = 2;
	if (split[1])
		(*env)->value = ft_strdup(split[1]);
	else if (!condition)
		(*env)->value = ft_strdup("");
	while (split && split[1] && split[i])
	{
		tmp = ft_strdup((*env)->value);
		free((*env)->value);
		(*env)->value = ft_strjoin(tmp, "=");
		free(tmp);
		tmp = ft_strdup((*env)->value);
		free((*env)->value);
		(*env)->value = ft_strjoin(tmp, split[i]);
		free(tmp);
		i++;
	}
}

static void	free_double(char **split, t_env *env)
{
	free_split(split);
	free(env);
}

t_env	*create_new_env(char *str)
{
	int		notset;
	t_env	*env;
	char	**split;

	if (!str || !(*str))
		return (NULL);
	if (str[0] == '=')
		print_error("=");
	if (str[0] == '=')
		return (NULL);
	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	notset = (ft_strchr(str, '=') == 0);
	split = ft_split(str, '=');
	if (!split || !(*split))
		return (NULL);
	if (!is_valid_name(split[0]))
	{
		free_double(split, env);
		return (NULL);
	}
	set_new_env(split, &env, notset);
	free_split(split);
	return (env);
}
