/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 17:50:03 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/27 09:37:47 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

struct s_global	g_global;

static int	check_blank(char *line)
{
	char	*tmp;

	tmp = ft_strtrim(line, "\n\t ");
	if (!tmp || tmp[0] == '\0')
	{
		if (tmp)
			free(tmp);
		return (0);
	}
	free(tmp);
	return (1);
}

static void	minishell_loop(t_minishell **minishell, char **env)
{
	char	*line;
	char	*prompt;

	while (42)
	{
		signal(SIGINT, &handle_signal);
		signal(SIGQUIT, SIG_IGN);
		prompt = get_prompt();
		line = readline(prompt);
		free(prompt);
		signal(SIGQUIT, &handle_signal);
		if (!line)
			ft_printf("exit\n");
		if (!line)
			break ;
		if (line[0] && line[0] != '\n')
			add_history(line);
		if (line[0] && check_blank(line) == 1)
		{
			(*minishell)->func = parsing(line, minishell);
			if ((*minishell)->func)
				execution(minishell, env);
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;

	(void)**argv;
	if (argc != 1)
	{
		write(STDERR_FILENO, "Saucishell: Error:", 18);
		write(STDERR_FILENO, "Too many arguments\n", 19);
		exit(EINVAL);
	}
	minishell = malloc(1 * sizeof(t_minishell));
	if (!minishell)
		return (1);
	initialize_minishell(env, &minishell);
	minishell_loop(&minishell, env);
	free_all(&minishell);
	return (0);
}
