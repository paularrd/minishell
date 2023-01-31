/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 14:40:02 by mrudloff          #+#    #+#             */
/*   Updated: 2023/01/28 15:54:36 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_exit(char **args, t_minishell **minishell, long long exit_code)
{
	free_split(args);
	exit_code %= 256;
	free_all(minishell);
	exit(exit_code);
}

static void	write_error(char **error, t_minishell **minishell)
{
	write(STDERR_FILENO, "saucishell: exit: ", 18);
	write(STDERR_FILENO, error[1], ft_strlen(error[1]));
	write(STDERR_FILENO, ": numeric argument required\n", 28);
	free_split(error);
	free_all(minishell);
	exit (2);
}

void	run_exit(char **args, t_minishell **minishell)
{
	int			limits;
	long long	exit_code;

	limits = 0;
	if (!args[1])
		free_split(args);
	if (!args[1])
		free_all(minishell);
	write(STDOUT_FILENO, "exit\n", 5);
	if (args[1])
	{
		exit_code = ft_atoll(args[1], &limits);
		if (limits == 1)
			write_error(args, minishell);
		if (args[2])
		{
			get_code_error(1, 1);
			ft_fprintf(STDERR_FILENO, "saucishell: exit: too many arguments\n");
			return ;
		}
		else
			free_exit(args, minishell, exit_code);
	}
	exit(EXIT_SUCCESS);
}
