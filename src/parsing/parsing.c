/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:19:07 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 11:23:40 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static t_function	*ft_create_func(void)
{
	t_function	*new_func;

	new_func = malloc(1 * sizeof(t_function));
	if (!new_func)
		return (NULL);
	new_func->check_execution = 1;
	new_func->fd_output = -2;
	new_func->fd_input = -2;
	new_func->check_export = 0;
	new_func->check_input = 0;
	new_func->cmd = NULL;
	new_func->next = NULL;
	return (new_func);
}

static char	*add_back(t_function **func, t_parsing *parse
, char *line, char **split)
{
	t_function	*start;
	t_function	*tmp;

	if (!(*func))
	{
		line = get_redir_heredoc(line, &parse, split);
		(*func) = ft_create_func();
		g_global.func = *func;
		(*func)->fd_input = parse->mini->fd_input;
		(*func)->check_execution = g_global.check_execution_here;
		(*func)->check_export = 1;
		(*func)->check_input = 0;
		return (line);
	}
	start = *func;
	while (start)
	{
		tmp = start;
		start = start->next;
	}
	line = get_redir_heredoc(line, &parse, split);
	tmp->next = ft_create_func();
	tmp->next->fd_input = parse->mini->fd_input;
	tmp->next->check_execution = 1;
	return (line);
}

static void	parsing_s_pipe(char **s_pipe, t_parsing *parse, t_function *func)
{
	int			i;

	i = 0;
	while (s_pipe[i] && parse->mini->fd_input != -3)
	{
		func->cmd = parse_cmd(ft_strdup(s_pipe[i]), &parse->mini, func);
		i++;
		func = func->next;
	}
	free(parse);
	free_split(s_pipe);
}

static int	parsing_error(t_minishell **minishell)
{
	if ((*minishell)->fd_input == -3)
	{
		free_func(g_global.func);
		(*minishell)->fd_input = -2;
		g_global.check_execution_here = 1;
		return (-1);
	}
	return (0);
}

t_function	*parsing(char *line, t_minishell **minishell)
{
	t_function	*func;
	t_parsing	*parse;
	char		**s_pipe;
	char		*tmp2;
	int			i;

	if (test_arg(line) != 1 || test_pipe(line) != 1 || test_redirect(line) != 1)
		return (NULL);
	parse = initialise_parse_struct(minishell);
	func = NULL;
	s_pipe = ft_split_pipe(line);
	free(line);
	if (!s_pipe)
		return (NULL);
	i = -1;
	while (s_pipe[++i] && parse->mini->fd_input != -3)
	{
		tmp2 = s_pipe[i];
		s_pipe[i] = add_back(&func, parse, ft_strdup(s_pipe[i]), s_pipe);
		free(tmp2);
	}
	parsing_s_pipe(s_pipe, parse, func);
	if (parsing_error(minishell) == -1)
		return (NULL);
	return (func);
}
