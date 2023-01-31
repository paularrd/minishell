/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 09:53:54 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 11:27:47 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static	void	free_doc(char **split, char *file, int fd[2], t_parsing **parse)
{
	close(fd[1]);
	close(fd[0]);
	if ((*parse)->mini->fd_input > 2)
		close((*parse)->mini->fd_input);
	free_split(split);
	split = NULL;
	free(g_global.line);
	free(file);
	free_all(&(*parse)->mini);
	free(*parse);
	split = NULL;
	file = NULL;
	*parse = NULL;
	exit(0);
}

static void	read_heredoc(t_parsing **parse, char *file, int fd[2], char **split)
{
	char	*tmp;

	while (1)
	{
		signal(SIGINT, &handle_child);
		signal(SIGQUIT, SIG_IGN);
		rl_clear_history();
		tmp = readline("> ");
		if (!tmp)
			ft_fprintf(STDERR_FILENO, "saucishell: warning: here-%s `%s')\n", \
				"document delimited by end-of-file (wanted", file);
		if (!tmp || ft_strcmp(tmp, file) == 0)
			break ;
		else if (tmp)
		{
			ft_fprintf(fd[1], "%s\n", tmp);
			free(tmp);
		}
	}
	if (tmp)
		free(tmp);
	free_doc(split, file, fd, parse);
}

static int	heredoc(t_parsing **parse, char *delim, char **split, char *line)
{
	int		fd[2];
	int		status;
	pid_t	pid;

	if (pipe(fd) == -1)
		perror("pipe");
	get_global(parse, delim, split, fd);
	g_global.line = line;
	pid = fork();
	g_global.pid = pid;
	if (pid == 0)
		read_heredoc(parse, delim, fd, split);
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	close(fd[1]);
	waitpid(pid, &status, 0);
	signal(SIGINT, &handle_signal);
	get_code_error(1, WEXITSTATUS(status));
	if (get_code_error(0, 0) == 130)
		close(fd[0]);
	if (get_code_error(0, 0) == 130)
		return (-3);
	return (fd[0]);
}

static char	*redirect_doc(char *line, t_parsing **parse, int *i, char **split)
{
	char	*file;
	int		start;
	int		fd_for_pipe;

	start = (*i);
	(*i) += 2;
	while (line[*i] && line[*i] == ' ')
		(*i)++;
	file = get_next_arg_no_env(&line[(*i)]);
	fd_for_pipe = heredoc(parse, file, split, line);
	line = del_redirection_heredoc(2, start, line, parse);
	g_global.check_execution_here = 1;
	if (!line || line[0] == '\0')
		g_global.check_execution_here = -1;
	if ((*parse)->mini->fd_input > 2)
		close((*parse)->mini->fd_input);
	(*parse)->mini->fd_input = fd_for_pipe;
	(*i) = 0;
	free(file);
	return (line);
}

char	*get_redir_heredoc(char *line, t_parsing **parse, char **split)
{
	int	i;
	int	test;

	i = 0;
	test = 1;
	while (line && line[i] && test == 1 && (*parse)->mini->fd_input != -3)
	{
		if (line[i] == '"' || line[i] == 39)
			i = next_quote(line, i);
		else if (test_prev(line, i, 2) == 1 && line[i] == '<' \
			&& line[i + 1] == '<' && ft_test_next(line, i + 2, &test) == 1)
			line = redirect_doc(line, parse, &i, split);
		else
			i++;
	}
	if (test == 0)
		return (NULL);
	return (line);
}
