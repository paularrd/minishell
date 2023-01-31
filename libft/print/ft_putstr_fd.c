/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fle-tolg <fle-tolg@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 10:02:00 by fle-tolg          #+#    #+#             */
/*   Updated: 2023/01/09 14:27:40 by fle-tolg         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	if (!s)
	{
		write(fd, "NULL", 4);
		return (4);
	}
	write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}
