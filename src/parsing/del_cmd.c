/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:55:57 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/25 10:37:25 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_n_char_3(char *line, int *i, int *y)
{
	(*i)++;
	while (line[*i] && line[*i] != 39)
	{
		(*y)++;
		(*i)++;
	}
	(*i)++;
}

static void	get_n_char_env(char *line, int *i, int *y)
{
	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		(*y)++;
		(*i)++;
	}
	(*i)++;
}

static int	get_n_char_del(char *line)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (line[i] && y == 0)
	{
		while ((ft_isprint(line[i]) == 1 && line[i] != ' ') \
			|| line[i] == '"' || line[i] == 39)
		{
			if (line[i] == '"')
				get_n_char_env(line, &i, &y);
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
	return (i);
}

char	*del_cmd(char *line)
{
	char	*new_line;
	int		i;

	i = get_n_char_del(line);
	if (i == 0 || i == (int)ft_strlen(line))
	{
		free(line);
		return (NULL);
	}
	new_line = ft_strdup(&line[i]);
	if (!new_line)
		return (NULL);
	free(line);
	return (new_line);
}
