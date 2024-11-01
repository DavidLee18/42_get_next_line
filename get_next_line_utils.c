/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:57:55 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/02 03:55:18 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*p;

	p = malloc(new_size);
	if (!p)
		return (free_(ptr));
	if (old_size < new_size)
		ft_memmove(p, ptr, old_size);
	else
		ft_memmove(p, ptr, new_size);
	free(ptr);
	ptr = NULL;
	return (p);
}

void	ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest < src)
	{
		i = n;
		while (i > 0)
		{
			((char *) dest)[i - 1] = ((char *)src)[i - 1];
			i--;
		}
		return ;
	}
	i = 0;
	while (i < n)
	{
		((char *) dest)[i] = ((char *)src)[i];
		i++;
	}
}

ssize_t	malloc_read(char **strp, int fd)
{
	*strp = (char *)malloc(BUFFER_SIZE);
	if (!*strp)
	{
		*strp = NULL;
		return (-1);
	}
	return (read(fd, *strp, BUFFER_SIZE));
}

char	*free_(char *p)
{
	if (p)
	{
		free(p);
		p = NULL;
	}
	return (NULL);
}
