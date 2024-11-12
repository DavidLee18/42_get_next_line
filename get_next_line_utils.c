/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:57:55 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/12 19:35:53 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_realloc(void **ptrp, size_t old_size, size_t new_size)
{
	void	*p;
	ssize_t	i;

	p = malloc(new_size);
	if (!p)
	{
		free_((char **)ptrp);
		return (0);
	}
	i = -1;
	while ((size_t)++i < new_size)
		*((char *)p + i) = '\0';
	if (old_size < new_size)
		ft_memmove(p, *ptrp, old_size);
	else
		ft_memmove(p, *ptrp, new_size);
	free(*ptrp);
	*ptrp = NULL;
	*ptrp = p;
	return (1);
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
		if ((*buf && **buf && *(*strp + idx) == '\n')
			|| (idx < 0 && *buf))
			return ;
		else
			offset = idx;
	}
	i = read(fd, *strp + offset, BUFFER_SIZE);
	if (i < 0 || (i == 0 && (!*strp || !**strp)))
		free_(strp);
	if (i == 0 && (!*strp || !*(*strp + offset)) && (*buf && !**buf))
		free_(buf);
	if (i <= 0)
		return ;
	if (take_line(strp, buf) >= BUFFER_SIZE)
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
