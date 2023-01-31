/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:50:53 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/23 14:51:58 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	**ft_strdup_split(char **split)
{
	char	**cpy_split;
	int		i;

	cpy_split = malloc((ft_count_arg(split) + 1) * sizeof(char *));
	if (!cpy_split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		cpy_split[i] = ft_strdup(split[i]);
		i++;
	}
	cpy_split[i] = NULL;
	return (cpy_split);
}
