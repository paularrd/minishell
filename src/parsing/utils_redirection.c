/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 13:16:15 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/27 16:26:29 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_test_next(char *line, int i, int *test)
{
	if (line[i] && (line[i] == '>' || line[i] == '<'))
	{
		ft_fprintf(2, "bash: syntax error near unexpected token `<'\n");
		*test = 0;
		return (0);
	}
	return (1);
}

void	get_n_char_2_no_env(char *line, int *i, int *y)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		(*y)++;
		(*i)++;
	}
	(*i)++;
}

void	get_next_arg_2_no_env(char *line, int *i, int *x, char *cmd)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		cmd[*x] = line[*i];
		(*x)++;
		(*i)++;
	}
	(*i)++;
}

int	get_size_next_arg_no_env(char *line)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (line[i] && y == 0)
	{
		while (line[i] && redir(line[i]) == 1)
		{
			if (line[i] == '"')
				get_n_char_2_no_env(line, &i, &y);
			else if (line[i] == 39)
				get_n_char_3(line, &i, &y);
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

char	*get_next_arg_no_env(char *line)
{
	char	*cmd;
	int		i;
	int		x;

	if (get_size_next_arg_no_env(line) == -1)
		return (NULL);
	cmd = ft_calloc((get_size_next_arg_no_env(line) + 1), sizeof(char));
	if (!cmd)
		return (NULL);
	i = 0;
	x = 0;
	while (line[i] && x < get_size_next_arg_no_env(line))
	{
		if (line[i] == '"')
			get_next_arg_2_no_env(line, &i, &x, cmd);
		else if (line[i] == 39)
			get_next_arg_3(line, &i, &x, cmd);
		else if (line[i] != '<' && line[i] != '>')
			simple_add_get_next_arg(&i, &x, line, cmd);
	}
	cmd[x] = '\0';
	return (cmd);
}
