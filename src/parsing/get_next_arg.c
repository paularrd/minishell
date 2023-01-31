/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 13:52:50 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/29 10:11:51 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_size_next_arg_env(int *i, int *y, char *line, t_parsing **parse)
{
	char	*tmp;
	char	*var_env;

	(*i)++;
	tmp = get_name_env(&line[*i]);
	var_env = get_value_env(tmp, parse);
	(*i) += ft_strlen(tmp);
	if (var_env)
		(*y) += ft_strlen(var_env);
	else if (*y == 0)
		(*y) = -1;
	free(var_env);
	free(tmp);
}

static int	get_size_next_arg(char *line, t_parsing **parse)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (line[i] && y == 0)
	{
		while (ft_isprint(line[i]) == 1 && redir(line[i]) == 1)
		{
			if (line[i] == '"')
				get_n_char_2(line, &i, &y, parse);
			else if (line[i] == 39)
				get_n_char_3(line, &i, &y);
			else if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
				get_size_next_arg_env(&i, &y, line, parse);
			else
			{
				y++;
				i++;
			}
		}
		if (line[i])
			i++;
	}
	return (y);
}

void	simple_add_get_next_arg(int *i, int *x, char *line, char *cmd)
{
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	cmd[*x] = line[*i];
	(*x)++;
	(*i)++;
}

void	initialize_integer_get_next_arg(int *i, int *x, t_parsing **parse)
{
	*i = 0;
	*x = 0;
	(*parse)->i = i;
	(*parse)->x = x;
}

char	*get_next_arg(char *line, t_parsing **parse)
{
	char	*cmd;
	int		i;
	int		x;

	if (get_size_next_arg(line, parse) == -1)
		return (NULL);
	cmd = ft_calloc((get_size_next_arg(line, parse) + 1), sizeof(char));
	if (!cmd)
		return (NULL);
	initialize_integer_get_next_arg(&i, &x, parse);
	while (line[i] && redir(line[i]) == 1 && x < get_size_next_arg(line, parse))
	{
		if (line[i] == '"')
			get_next_arg_2(line, cmd, parse);
		else if (line[i] == 39)
			get_next_arg_3(line, &i, &x, cmd);
		else if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
			get_next_arg_simple_env(line, cmd, parse);
		else
			simple_add_get_next_arg(&i, &x, line, cmd);
	}
	cmd[x] = '\0';
	return (cmd);
}
