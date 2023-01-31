/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:55:40 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 11:23:28 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	test_next_arg(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '\0' || line[i] == '|')
	{
		ft_fprintf(2, "saucishell: syntax error near unexpected token `|\n");
		return (0);
	}
	return (1);
}

static int	ft_test_pipe2(char *line)
{
	int	i;

	i = 1;
	while (line[i] && line[i] != '"')
		i++;
	i++;
	return (i);
}

int	test_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			i += ft_test_pipe2(&line[i]);
		else if (line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
			i++;
		}
		else if (line[i] == '|')
		{
			if (test_next_arg(&line[i]) == 0)
				return (0);
			i++;
		}
		else
			i++;
	}
	return (1);
}

int	next_char_fill(char *line, char c, int *x, char *s)
{
	int	i;

	s[*x] = line[0];
	(*x)++;
	i = 1;
	while (line[i] && line[i] != c)
	{
		s[*x] = line[i];
		i++;
		(*x)++;
	}
	if (line[i] == c)
	{
		s[*x] = line[i];
		(*x)++;
		i++;
	}
	return (i);
}
