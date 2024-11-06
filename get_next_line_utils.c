/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:57:55 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/07 00:28:54 by jaehylee         ###   ########.fr       */
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
	ssize_t	i;

	if (dest > src)
	{
		i = (ssize_t)n;
		while (--i >= 0)
			((char *) dest)[i] = ((char *)src)[i];
		return ;
	}
	i = -1;
	while (++i < (ssize_t)n)
		((char *) dest)[i] = ((char *)src)[i];
}

char	*free_(char **p)
{
	if (*p)
	{
		free(*p);
		*p = NULL;
	}
	return (NULL);
}

void	read_loop(int fd, char **strp, size_t offset, char **buf)
{
	ssize_t	i;
	ssize_t	idx;

	if (!*strp)
	{
		idx = take_buf(strp, buf);
		if (idx < 0 && ((*buf && **buf && *(*strp + idx) == '\n') || *buf))
			return ;
		if (idx < 0 && !*buf)
			offset = ft_strlen(*strp);
		else
			offset = idx;
	}
	i = read(fd, *strp + offset, BUFFER_SIZE);
	if (i < 0 || (i == 0 && (!*strp || !**strp)))
		free_(strp);
	if (i == 0 && (!*strp || !*(*strp + offset)) && (*buf && !**buf))
		free_(buf);
	if (i == 0)
		return ;
	if (take_line(strp, buf) == BUFFER_SIZE)
		read_loop(fd, strp, offset + BUFFER_SIZE, buf);
}

size_t	ft_strlen(char *str)
{
	size_t	l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}
