/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_get_next_arg.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:57:45 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/25 10:44:26 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_is_char_env(char c)
{
	if (ft_isdigit(c) == 1 || c == '_')
		return (1);
	return (0);
}

void	get_next_arg_simple_env(char *line, char *cmd, t_parsing **parse)
{
	char	*tmp;
	char	*var_env;
	int		*i;
	int		*x;

	i = (*parse)->i;
	x = (*parse)->x;
	(*i)++;
	tmp = get_name_env(&line[*i]);
	var_env = get_value_env(tmp, parse);
	(*i) += ft_strlen(tmp);
	if (var_env)
	{
		ft_strcat(cmd, var_env);
		(*x) += ft_strlen(var_env);
	}
	free(var_env);
	free(tmp);
}

void	get_next_arg_3(char *line, int *i, int *x, char *cmd)
{
	(*i)++;
	while (line[*i] && line[*i] != 39)
	{
		cmd[*x] = line[*i];
		(*x)++;
		(*i)++;
	}
	(*i)++;
}

static void	part_2_next_arg_2(char *line, char *cmd, t_parsing **parse)
{
	char	*tmp;
	char	*var_env;
	int		*i;
	int		*x;

	i = (*parse)->i;
	x = (*parse)->x;
	(*i)++;
	tmp = get_name_env(&line[*i]);
	var_env = get_value_env(tmp, parse);
	(*i) += ft_strlen(tmp);
	if (var_env)
	{
		ft_strcat(cmd, var_env);
		(*x) += ft_strlen(var_env);
	}
	free(var_env);
	free(tmp);
}

void	get_next_arg_2(char *line, char *cmd, t_parsing **parse)
{
	int		*i;
	int		*x;

	i = (*parse)->i;
	x = (*parse)->x;
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$' && line[(*i) + 1] && line[(*i) + 1] != ' ' \
			&& line[(*i) + 1] != '"')
		{
			part_2_next_arg_2(line, cmd, parse);
		}
		else if (line[*i])
		{
			cmd[*x] = line[*i];
			(*x)++;
			(*i)++;
		}
	}
	(*i)++;
}
