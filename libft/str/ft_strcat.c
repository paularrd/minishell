/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 10:56:39 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/21 12:26:06 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	y;

	i = ft_strlen(dest);
	y = 0;
	while (src[y])
	{
		dest[i] = src[y];
		i++;
		y++;
	}
	return (dest);
}
