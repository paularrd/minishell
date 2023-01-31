/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirection_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:20:34 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/27 14:59:48 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*redirect_two(char *line, t_parsing **parse, int *i, t_function **func)
{
	char	*file;
	int		start;

	start = (*i);
	(*i) += 2;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	file = get_next_arg(&line[(*i)], parse);
	line = del_redirection(2, start, line, parse);
	if ((*func)->fd_input > 2)
		close((*func)->fd_input);
	(*func)->fd_input = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
	if ((*func)->fd_input == -1)
	{
		if ((*func)->check_input != -1)
			perror(file);
		get_code_error(1, 1);
		(*func)->check_execution = -1;
		(*func)->check_input = -1;
	}
	(*i) = 0;
	return (line);
}

static void	double_inc(int *i, int *y)
{
	*i += 1;
	*y += 1;
}

int	size_new_line(int i, int start, char *line, t_parsing **parse)
{
	int		y;

	y = 0;
	while (line[i] && y == 0)
	{
		while (ft_isprint(line[i]) == 1 && line[i] != ' ' \
			&& line[i] != '>' && line[i] != '<')
		{
			if (line[i] == '"')
				get_n_char_2(line, &i, &y, parse);
			else if (line[i] == 39)
				get_n_char_3(line, &i, &y);
			else if (line[i] == '$' && line[i + 1] && line[i + 1] != ' ')
				get_size_next_arg_env(&i, &y, line, parse);
			else
				double_inc(&i, &y);
		}
		if (line[i] && line[i] != '>' && line[i] != '<')
			i++;
	}
	if (start != 0)
		return (start + ft_strlen(&line[i]));
	return (ft_strlen(line) - i);
}

int	test_prev(char *line, int i, int size)
{
	if (i == 0)
		return (1);
	else if (line[i - 1] == '"' && ((i + size) < (int)ft_strlen(line) \
		&& line[i + size] == '"'))
		return (0);
	else if (line[i - 1] == 39 && ((i + size) < (int)ft_strlen(line)) \
		&& line[i + size] == 39)
		return (0);
	return (1);
}

int	next_quote(char *line, int i)
{
	if (line[i] == '"')
	{
		i++;
		while (line[i] && line[i] != '"')
			i++;
		if (line[i])
			i++;
	}
	else if (line[i] == 39)
	{
		i++;
		while (line[i] && line[i] != 39)
			i++;
		if (line[i])
			i++;
	}
	return (i);
}
