/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 17:16:48 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 11:20:54 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*del_redirection(int size, int x, char *line, t_parsing **parse)
{
	char	*nl;
	int		i;
	int		y;

	nl = malloc(size_new_line((x + size), x, line, parse) + 1 * sizeof(char));
	if (!nl)
		return (NULL);
	i = 0;
	y = 0;
	while (i < x)
	{
		nl[y] = line[i];
		i++;
		y++;
	}
	i += (ft_strlen(line) - size_new_line((x + size), x, line, parse));
	while (line[i])
	{
		nl[y] = line[i];
		y++;
		i++;
	}
	nl[y] = '\0';
	free(line);
	return (nl);
}

static char	*input(char *line, t_parsing **parse, int *i, t_function **func)
{
	char	*file;
	int		start;

	start = (*i);
	(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	file = get_next_arg(&line[(*i)], parse);
	line = del_redirection(1, start, line, parse);
	if ((*func)->fd_input > 2)
		close((*func)->fd_input);
	(*func)->fd_input = open(file, O_RDONLY);
	if ((*func)->fd_input == -1)
	{
		if ((*func)->check_input != -1)
			perror(file);
		get_code_error(1, 1);
		(*func)->check_execution = -1;
		(*func)->check_input = -1;
	}
	(*i) = 0;
	free(file);
	return (line);
}

static char	*output(char *line, t_parsing **parse, int *i, t_function **func)
{
	char	*file;
	int		start;

	start = (*i);
	(*i)++;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	file = get_next_arg(&line[(*i)], parse);
	line = del_redirection(1, start, line, parse);
	if ((*func)->fd_output > 2)
		close((*func)->fd_output);
	if ((*func)->fd_output != -1 && (*func)->check_input != -1)
		(*func)->fd_output = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if ((*func)->fd_output == -1)
	{
		if ((*func)->check_input != -1)
			perror(file);
		get_code_error(1, 1);
		(*func)->check_execution = -1;
		(*func)->check_input = -1;
	}
	(*i) = 0;
	free(file);
	return (line);
}

static char	*append(char *line, t_parsing **parse, int *i, t_function **func)
{
	char	*file;
	int		start;

	start = (*i);
	(*i) += 2;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	file = get_next_arg(&line[(*i)], parse);
	line = del_redirection(2, start, line, parse);
	if ((*func)->fd_output > 2)
		close((*func)->fd_output);
	if ((*func)->fd_output != -1 && (*func)->check_input != -1)
			(*func)->fd_output = open(file, O_CREAT
				| O_WRONLY | O_APPEND, 0644);
	if ((*func)->fd_output == -1)
	{
		if ((*func)->check_input != -1)
			perror(file);
		get_code_error(1, 1);
		(*func)->check_execution = -1;
		(*func)->check_input = -1;
	}
	(*i) = 0;
	free(file);
	return (line);
}

char	*get_redirection(char *line, t_parsing **parse, t_function **func)
{
	int	i;
	int	test;

	i = 0;
	test = 1;
	while (line && line[i] && test == 1)
	{
		if (line[i] == '"' || line[i] == 39)
			i = next_quote(line, i);
		else if (line[i] == '<' && line[i + 1] && line[i + 1] == '>')
			line = redirect_two(line, parse, &i, func);
		else if (test_prev(line, i, 1) && line[i] == '<' && line[i + 1] != '<')
			line = input(line, parse, &i, func);
		else if (test_prev(line, i, 1) == 1 && line[i] == '>' \
			&& line[i + 1] != '>' && ft_test_next(line, i + 1, &test) == 1)
			line = output(line, parse, &i, func);
		else if (test_prev(line, i, 2) == 1 && line[i] == '>' \
			&& line[i + 1] == '>' && ft_test_next(line, i + 2, &test) == 1)
			line = append(line, parse, &i, func);
		else
			i++;
	}
	if (test == 0)
		return (NULL);
	return (line);
}
