/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 12:44:19 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 17:37:18 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	handle_signal(int signum)
{
	if (g_global.pid != 0)
	{
		if (!kill(g_global.pid, signum))
		{
			if (signum == SIGINT)
			{
				write(STDOUT_FILENO, "\n", 1);
				get_code_error(1, 130);
				return ;
			}
		}
	}
	if (signum == SIGQUIT)
	{
		write(STDERR_FILENO, "Quit (code dumped)\n", 19);
		get_code_error(1, 131);
	}
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		get_code_error(1, 130);
	}
}

void	handle_child(int signum)
{
	if (signum == SIGQUIT)
		exit(131);
	free_split(g_global.split);
	close(g_global.fd1);
	close(g_global.fd2);
	free(g_global.line);
	free(g_global.file);
	free_all(&g_global.parse->mini);
	free(g_global.parse);
	write(1, "\n", 1);
	exit(130);
}
