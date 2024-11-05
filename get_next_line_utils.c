/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:57:55 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/05 10:11:08 by jaehylee         ###   ########.fr       */
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

char	*free_(char *p)
{
	if (p)
	{
		free(p);
		p = NULL;
	}
	return (NULL);
}

void	read_loop(int fd, char **strp, size_t offset, char **buf)
{
	ssize_t	i;
	size_t	end;
	size_t	idx;

	if (!*strp)
	{
		idx = take_buf(strp, buf);
		if (**buf || *strp[idx] == '\n')
			return ;
		offset = idx;
	}
	i = read(fd, *strp + offset, BUFFER_SIZE);
	if (i < 0 || (i == 0 && !*strp))
	{
		free_(*strp);
		return ;
	}
	else if (i == 0)
		return ;
	end = take_line(strp, offset, buf, i);
	if (end == BUFFER_SIZE)
		read_loop(fd, strp, offset + BUFFER_SIZE, buf);
}
