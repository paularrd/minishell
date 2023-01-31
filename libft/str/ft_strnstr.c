/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 10:20:31 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/09 14:28:16 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	y;
	char	*str;

	str = (char *)big;
	if (len == 0 && (!big || !little))
		return (NULL);
	if (little[0] == '\0')
		return (str);
	i = 0;
	while (str[i] && i < len)
	{
		y = 0;
		while (str[i] == little[y] && i < len)
		{
			if (little[y + 1] == '\0')
				return (str + (i - y));
			i++;
			y++;
		}
		i -= y;
		i++;
	}
	return (NULL);
}
