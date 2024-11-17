/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:57:55 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/17 13:56:05 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_realloc(void **ptrp, const size_t old_size, const size_t new_size)
{
	void	*p;
	ssize_t	i;

	p = malloc(new_size);
	if (!p)
	{
		if (old_size != 0)
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
	if (old_size != 0)
		free_((char **)ptrp);
	*ptrp = p;
	return (1);
}

void	ft_memmove(void *dest, const void *src, const size_t n)
{
	ssize_t	i;

	if (dest > src)
	{
		i = (ssize_t)n;
		while (--i >= 0)
			((unsigned char *) dest)[i] = ((unsigned char *)src)[i];
		return ;
	}
	i = -1;
	while ((size_t)++i < n)
		((unsigned char *) dest)[i] = ((unsigned char *)src)[i];
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

void	read_loop(const int fd, char **strp, size_t offset, char **temp)
{
	ssize_t	i;
	ssize_t	idx;

	if (!*strp)
	{
		idx = take_temp(strp, temp);
		if ((*temp && **temp && *(*strp + idx) == '\n') || idx < 0)
			return ;
		offset = idx;
	}
	else if (offset != 0 && *(*strp + offset - 1) == '\n')
		return ;
	i = read(fd, *strp + offset, BUFFER_SIZE);
	if (i < 0 || (i == 0 && *strp && !**strp))
		free_(strp);
	if (i == 0 && (!*strp || !*(*strp + offset)) && (*temp && !**temp))
		free_(temp);
	if (i <= 0)
		return ;
	idx = take_line(strp, offset + i, temp);
	if (idx >= 0)
		read_loop(fd, strp, idx, temp);
}

size_t	ft_strlen(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}
