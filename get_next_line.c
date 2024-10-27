/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:46:12 by jaehylee          #+#    #+#             */
/*   Updated: 2024/10/25 22:49:45 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*str;
	ssize_t	i;
	size_t	l;

	i = malloc_read(&str, fd);
	l = 0;
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
