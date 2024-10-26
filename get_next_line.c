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

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 8
#endif
#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*str;
	ssize_t	i;
	size_t	l;

	i = 0;
	l = 0;
	str = (char *)malloc(BUFFER_SIZE * sizeof(char));
	if (!str)
		return (NULL);
	while (1)
	{
		i = read(fd, str + l, BUFFER_SIZE);
		if (i < 0)
			return (NULL);
		else if (i < BUFFER_SIZE)
			return (str);
		str = ft_realloc(str, l, l + BUFFER_SIZE);
		l += BUFFER_SIZE;
	}
}
