/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 11:00:08 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 10:42:31 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_global(t_parsing **parse, char *delim, char **split, int fd[2])
{
	g_global.file = delim;
	g_global.split = split;
	g_global.parse = *parse;
	g_global.fd1 = fd[0];
	g_global.fd2 = fd[1];
}

int	redir(char c)
{
	if (c == '>' || c == '<' || c == ' ')
		return (0);
	if (ft_isalnum(c) == 1)
		return (1);
	return (1);
}

char	*del_redirection_heredoc(int size, int x, char *line, t_parsing **parse)
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
