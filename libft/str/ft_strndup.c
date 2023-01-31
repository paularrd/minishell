/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrudloff <mrudloff@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 11:51:30 by mrudloff          #+#    #+#             */
/*   Updated: 2023/01/17 12:12:30 by mrudloff         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strndup(const char *s, int size)
{
	int		i;
	char	*str;

	if (size < 0 || !s)
		return (NULL);
	i = 0;
	while (s[i])
		i++;
	if (i > size)
		i = size;
	str = malloc((i + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < size)
		str[i] = s[i];
	str[i] = '\0';
	return (str);
}
