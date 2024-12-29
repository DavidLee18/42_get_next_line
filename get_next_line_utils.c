/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:57:55 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/25 07:44:28 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	take_line(char **strp, const size_t until, char **temp);
ssize_t	add_substr(char **srcp, const size_t src_len, const size_t from,
			char **destp);
size_t	ft_realloc(void **ptrp, const size_t old_size, const size_t new_size);
void	ft_memmove_(void *dest, const void *src, const size_t n);
size_t	ft_strlen(const char *str);

ssize_t	take_line(char **strp, const size_t until, char **temp)
{
	size_t	k;
	ssize_t	res;
	size_t	alloc;

	if (!*temp)
	{
		alloc = ft_realloc((void **)temp, 0, 1);
		if (!alloc)
			return (-1);
	}
	k = 0;
	if (!*strp)
		return (-1);
	while (k < until && *(*strp + k) && *(*strp + k) != '\n')
		k++;
	res = add_substr(strp, until, k, temp);
	if (res < 0)
		return (res);
	alloc = ft_realloc((void **)strp, res + 1, res + 1 + BUFFER_SIZE);
	if (!alloc)
		return (-1);
	return (res);
}

ssize_t	add_substr(char **srcp, const size_t src_len, const size_t from,
	char **destp)
{
	size_t	dest_len;
	size_t	alloc;

	if (!*srcp)
		return (-1);
	if (from != 0 && from == src_len)
		return ((ssize_t)src_len);
	dest_len = ft_strlen(*destp);
	alloc = ft_realloc((void **)destp, dest_len + 1,
			dest_len + src_len - from);
	if (!alloc)
		return (-1);
	ft_memmove_(*destp + dest_len, *srcp + from + 1, src_len - from - 1);
	*(*destp + dest_len + src_len - from - 1) = '\0';
	alloc = ft_realloc((void **)srcp, src_len, from + 2);
	if (!alloc)
		return (-1);
	*(*srcp + from + 1) = '\0';
	return ((ssize_t)from + 1);
}

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
		ft_memmove_(p, *ptrp, old_size);
	else
		ft_memmove_(p, *ptrp, new_size);
	if (old_size != 0)
		free_((char **)ptrp);
	*ptrp = p;
	return (1);
}

void	ft_memmove_(void *dest, const void *src, const size_t n)
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

size_t	ft_strlen_(const char *str)
{
	size_t	l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}
