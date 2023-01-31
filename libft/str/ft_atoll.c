/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudloff <mrudloff@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 15:37:35 by mrudloff          #+#    #+#             */
/*   Updated: 2023/01/25 09:53:55 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static long long	atoll_loop(const char *nptr, int i, int *limits)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	if (i < 0)
		sign *= -1;
	if (i < 0)
		i *= -1;
	while (ft_isalnum(nptr[i]))
	{
		if (ft_isdigit(nptr[i]))
		{
			result = (result * 10) + (nptr[i] - '0');
			if (((i == 18 && sign == 1) && (nptr[i] > '7' && nptr[i] <= '9'))
				|| ((i == 19 && sign == -1) && (nptr[i] == '9')))
				*limits = 1;
		}
		else
			*limits = 1;
		i++;
	}
	return (result * sign);
}

long long	ft_atoll(const char *nptr, int *limits)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-')
		sign *= -1;
	i += (nptr[i] == '+' || nptr[i] == '-');
	result = atoll_loop(nptr, i * sign, limits);
	return (result);
}
