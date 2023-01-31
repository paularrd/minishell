/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 16:25:32 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/28 11:33:26 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	malloc_error(char **splitted, int i)
{
	int	y;

	y = 0;
	while (y < i)
	{
		free(splitted[y]);
		y++;
	}
	free(splitted);
}

static int	nb_str(char *str)
{
	int	i;
	int	x;

	if (!str[0])
		return (0);
	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '"')
			i += next_char_no_x(&str[i], '"');
		else if (str[i] == 39)
			i += next_char_no_x(&str[i], 39);
		else if (str[i] == '|')
		{
			i++;
			x++;
		}
		else if (str[i])
			i++;
	}
	if (str[i - 1] != '|')
		x++;
	return (x);
}

static int	nb_char(char *str, int i)
{
	int	y;
	int	x;
	int	z;

	init_int(&y, &z, &x);
	while (y < (int)ft_strlen(str) && str[y])
	{
		if (str[y] == '"')
			y += next_char(&str[i], '"', &x);
		else if (str[y] == 39)
			y += next_char(&str[i], 39, &x);
		else if (str[y] != '|')
		{
			while (str[y] && (str[y] != '|' || ft_is_in_quote(y, str) == 0))
			{
				if (z == i)
					x++;
				y++;
			}
			z++;
		}
		else if (str[y])
			y++;
	}
	return (x);
}

static void	fill_tab(char *str, int i, char *new_str)
{
	int	y;
	int	x;
	int	z;

	init_int(&y, &z, &x);
	while (str[y])
	{
		if (str[y] == '"')
			y += next_char_fill(&str[y], '"', &x, new_str);
		else if (str[y] == 39)
			y += next_char_fill(&str[y], 39, &x, new_str);
		else if (str[y] != '|')
		{
			if (z == i)
			{
				while (str[y] && (str[y] != '|' || ft_is_in_quote(y, str) == 0))
					new_str[x++] = str[y++];
			}
			while (str[y] && (str[y] != '|' || ft_is_in_quote(y, str) == 0))
				y++;
			z++;
		}
		else if (str[y])
			y++;
	}
}

char	**ft_split_pipe(char *str)
{
	char		**splitted;
	int			i;
	int			x;

	if (!str)
		return (NULL);
	x = nb_str(str);
	splitted = malloc((x + 1) * sizeof(char *));
	if (!splitted)
		return (NULL);
	i = 0;
	while (i < x)
	{
		splitted[i] = ft_calloc((nb_char(str, i) + 1), sizeof(char));
		if (!splitted[i])
		{
			malloc_error(splitted, i);
			return (NULL);
		}
		fill_tab(str, i, splitted[i]);
		i++;
	}
	splitted[i] = NULL;
	return (splitted);
}
