/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:59:46 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/29 10:10:55 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_name_env(char *line_env)
{
	char	*var_env;
	int		i;

	i = 0;
	if (line_env[i] == '?')
		return (ft_strdup("?"));
	while (line_env[i] && (line_env[i] == '_' || \
		ft_isalpha(line_env[i]) == 1) && line_env[i] != ' ')
		i++;
	var_env = malloc((i + 1) * sizeof(char));
	if (!var_env)
		return (NULL);
	i = 0;
	while (line_env[i] && (line_env[i] == '_' || \
		ft_isalpha(line_env[i]) == 1) && line_env[i] != ' ')
	{
		var_env[i] = line_env[i];
		i++;
	}
	var_env[i] = '\0';
	return (var_env);
}

char	*get_value_env(char *str, t_parsing **parse)
{
	t_env	*env;
	char	*code_error;

	if (ft_strcmp(str, "?") == 0)
	{
		code_error = ft_itoa(get_code_error(0, 0));
		return (code_error);
	}
	env = get_env(str, &(*parse)->mini->lst_env);
	if (!env)
		return (NULL);
	return (ft_strdup(env->value));
}

char	*trim_and_free(char *line, char *delim)
{
	char	*tmp;

	tmp = ft_strtrim(line, delim);
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
	return (line);
}
