/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 17:05:12 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 11:23:36 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*test_next_simple(int *i, char *line)
{
	(*i)++;
	while (line[*i] && line[*i] == ' ' && line[*i] != '>' && line[*i] != '<')
		(*i)++;
	if (line[*i] == '\0' || line[*i] == '>' || line[*i] == '<')
	{
		ft_fprintf(2, "saucishell: syntax error\n");
		get_code_error(1, 2);
		(*i) = 0;
		return (NULL);
	}
	return (line);
}

static char	*test_next_double(int *i, char *line)
{
	(*i) += 2;
	while (line[*i] && line[*i] == ' ' && line[*i] != '>' && line[*i] != '<')
		(*i)++;
	if (line[*i] == '\0' || line[*i] == '>' || line[*i] == '<')
	{
		ft_fprintf(2, "saucishell: syntax error\n");
		get_code_error(1, 2);
		(*i) = 0;
		return (NULL);
	}
	return (line);
}

static void	go_to_next(char c, int *i, char *line)
{
	(*i)++;
	if (c == 39)
		while (line[*i] && line[*i] != 39)
			(*i)++;
	if (c == '"')
		while (line[*i] && line[*i] != '"')
			(*i)++;
	(*i)++;
}

int	test_redirect(char *line)
{
	int	i;

	i = 0;
	while (line && line[i])
	{
		if (line[i] == 39 || line[i] == '"')
			go_to_next(line[i], &i, line);
		else if (line[i] == '>' && line[i + 1] != '>' && line[i + 1] != '<')
			line = test_next_simple(&i, line);
		else if (line[i] == '<' && line[i + 1] != '>' && line[i + 1] != '<')
			line = test_next_simple(&i, line);
		else if (line[i] == '>' && line[i + 1] == '>')
			line = test_next_double(&i, line);
		else if (line[i] == '<' && line[i + 1] == '<')
			line = test_next_double(&i, line);
		else
			i++;
	}
	if (!line)
		return (0);
	return (1);
}
