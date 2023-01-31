/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudloff <mrudloff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:04:29 by mrudloff          #+#    #+#             */
/*   Updated: 2023/01/27 16:09:12 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	check_unset_arg(char **args)
{
	int	i;

	i = 1;
	while (args && args[i])
	{
		is_valid_name(args[i]);
		i++;
	}
}
