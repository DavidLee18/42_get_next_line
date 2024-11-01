/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:46:12 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/01 16:09:37 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*str;
	ssize_t	i;
	size_t	l;

	i = malloc_read(&str, fd);
	l = BUFFER_SIZE;
	if (i <= 0)
		return (free_(str));
	else if (i < BUFFER_SIZE)
		return (str);
	str = (char *)ft_realloc(str, l, l + BUFFER_SIZE);
	while (str)
	{
		l += BUFFER_SIZE;
		i = read(fd, str + l, BUFFER_SIZE);
		if (i < 0)
			return (free_(str));
		else if (i < BUFFER_SIZE)
			return (str);
		str = (char *)ft_realloc(str, l, l + BUFFER_SIZE);
	}
	return (NULL);
}
