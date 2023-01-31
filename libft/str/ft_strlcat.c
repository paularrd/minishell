/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:27:51 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/09 14:28:03 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	y;

	i = 0;
	while (i < size && dst[i])
		i++;
	y = i;
	if (size == 0)
		return (y + ft_strlen(src));
	while (i < (size - 1) && src[i - y])
	{
		dst[i] = src[i - y];
		i++;
	}
	if (y < size)
		dst[i] = '\0';
	return (y + ft_strlen(src));
}
