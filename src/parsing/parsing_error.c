/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:00:01 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 11:23:14 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	reduce_test_quote(int *i, int *counter, char *line, char c)
{
	(*i)++;
	(*counter)++;
	while (line[*i] && line[*i] != c)
		(*i)++;
	if (line[*i] && line[*i] == c)
	{
		(*counter)++;
		(*i)++;
	}
}

int	test_double_quote(char *line)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == '"')
			reduce_test_quote(&i, &counter, line, '"');
		else if (line[i] == 39)
		{
			i++;
			while (line[i] && line[i] != 39)
				i++;
			if (line[i] == 39)
				i++;
		}
		else
			i++;
	}
	if (counter != 0 && counter % 2 != 0)
		return (0);
	return (1);
}

int	test_simple_quote(char *line)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (line[i])
	{
		if (line[i] == 39)
			reduce_test_quote(&i, &counter, line, 39);
		else if (line[i] == '"')
		{
			i++;
			while (line[i] && line[i] != '"')
				i++;
			if (line[i] == '"')
				i++;
		}
		else
			i++;
	}
	if (counter != 0 && counter % 2 != 0)
		return (0);
	return (1);
}

int	test_arg(char *line)
{
	if (test_simple_quote(line) == 0 || test_double_quote(line) == 0)
	{
		ft_fprintf(2, "bash: %s\n", strerror(22));
		return (EINVAL);
	}
	return (1);
}

char	**create_blank_tab(void)
{
	char	**split;

	split = malloc(2 * sizeof(char *));
	if (!split)
		return (NULL);
	split[0] = ft_strdup("");
	split[1] = NULL;
	return (split);
}
