/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/08 16:39:56 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/26 14:54:39 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_args(char *str)
{
	int	i;
	int	opt_n;

	i = 2;
	opt_n = 0;
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		opt_n = 1;
		while (str[i])
		{
			if (str[i] != 'n')
				opt_n = 0;
			if (str[i] != 'n')
				break ;
			i++;
		}
	}
	return (opt_n);
}

static void	close_fd(void)
{
	close(0);
	close(1);
	close(2);
}

void	cmd_echo(char **args)
{
	int	i;
	int	opt_n;

	opt_n = 0;
	if (!args[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	i = 1;
	while (args && args[i] && check_args(args[i]))
		i++;
	if (i != 1)
		opt_n = 1;
	while (args && args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!opt_n)
		write(STDOUT_FILENO, "\n", 1);
	close_fd();
}
