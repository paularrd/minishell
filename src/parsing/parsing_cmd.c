/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 12:05:14 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/26 14:53:47 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	get_n_char_2(char *line, int *i, int *y, t_parsing **parse)
{
	char	*tmp;
	char	*var_env;

	(*i)++;
	while (line[*i] && line[*i] != '"')
	{
		if (line[*i] == '$' && line[(*i) + 1] && line[(*i) + 1] != ' ' && \
			line[(*i) + 1] != '"')
		{
			(*i)++;
			tmp = get_name_env(&line[*i]);
			var_env = get_value_env(tmp, parse);
			(*i) += ft_strlen(tmp);
			if (var_env)
				(*y) += ft_strlen(var_env);
			free(tmp);
			free(var_env);
		}
		else
		{
			(*y)++;
			(*i)++;
		}
	}
	(*i)++;
}

int	get_n_char(char *line, t_parsing **parse)
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
				get_n_char_2(line, &i, &y, parse);
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

static char	**ft_add_split(char **splitted, char *str)
{
	char	**new_splitted;
	int		i;

	if (!str)
		return (splitted);
	if (!splitted)
	{
		new_splitted = malloc(2 * sizeof(char *));
		if (!new_splitted)
			return (NULL);
		new_splitted[0] = ft_strdup(str);
		new_splitted[1] = NULL;
		return (new_splitted);
	}
	new_splitted = malloc((ft_count_arg(splitted) + 2) * sizeof(char *));
	if (!new_splitted)
		return (NULL);
	i = -1;
	while (splitted[++i])
		new_splitted[i] = ft_strdup(splitted[i]);
	new_splitted[i] = ft_strdup(str);
	new_splitted[i + 1] = NULL;
	free_split(splitted);
	return (new_splitted);
}

t_parsing	*initialise_parse_struct(t_minishell **minishell)
{
	t_parsing	*parse;

	parse = malloc(1 * sizeof(t_parsing));
	if (!parse)
		return (NULL);
	parse->mini = *minishell;
	return (parse);
}

char	**parse_cmd(char *line, t_minishell **mini, t_function *func)
{
	t_parsing	*parse;
	char		**cmd;
	char		*tmp;

	parse = initialise_parse_struct(mini);
	cmd = NULL;
	line = trim_and_free(line, " ");
	line = get_redirection(line, &parse, &func);
	if (line[0] == '\0')
		cmd = create_blank_tab();
	while (line)
	{
		tmp = get_next_arg(line, &parse);
		cmd = ft_add_split(cmd, tmp);
		free(tmp);
		line = del_cmd(line);
		tmp = ft_strtrim(line, " ");
		free(line);
		line = ft_strdup(tmp);
		free(tmp);
	}
	free(parse);
	return (cmd);
}
