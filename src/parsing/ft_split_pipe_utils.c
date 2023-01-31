/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:22:06 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/26 17:16:10 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_int(int *i, int *z, int *y)
{
	*i = 0;
	*z = 0;
	*y = 0;
}

int	next_char_no_x(char *line, char c)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != c)
	{
		i++;
	}
	if (line[i] == c)
		i++;
	return (i);
}

int	next_char(char *line, char c, int *x)
{
	int	i;

	i = 1;
	(*x)++;
	while (line[i] && line[i] != c)
	{
		i++;
		(*x)++;
	}
	if (line[i] == c)
	{
		(*x)++;
		i++;
	}
	return (i);
}

static int	ft_is_in_quote_2(char *s, int *i, int y)
{
	(*i)++;
	while (s[*i] && s[*i] != '"' && *i < y)
		(*i)++;
	if (*i == y)
		return (0);
	else if (s[*i])
		(*i)++;
	return (1);
}

int	ft_is_in_quote(int y, char *s)
{
	int	i;

	i = 0;
	while (s[i] && i < y)
	{
		if (s[i] == '"')
		{
			if (ft_is_in_quote_2(s, &i, y) == 0)
				return (0);
		}
		else if (s[i] == 39)
		{
			i++;
			while (s[i] && s[i] != 39 && i < y)
				i++;
			if (i == y)
				return (0);
			else if (s[i])
				i++;
		}
		else if (s[i])
			i++;
	}
	return (1);
}
