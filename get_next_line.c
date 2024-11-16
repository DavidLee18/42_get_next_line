/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:46:12 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/16 21:14:33 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*str;
	static char		*buf;

	str = NULL;
	if (fd >= 0)
		read_loop(fd, &str, 0, &buf);
	return (str);
}

ssize_t	take_line(char **strp, size_t until, char **buf)
{
	size_t	k;
	ssize_t	res;
	size_t	alloc;

	if (!*buf)
	{
		alloc = ft_realloc((void **)buf, 0, 1);
		if (!alloc)
			return (-1);
	}
	k = 0;
	if (!*strp)
		return (-1);
	while (k < until && *(*strp + k) && *(*strp + k) != '\n')
		k++;
	res = add_substr(strp, until, k, buf);
	if (res < 0)
		return (res);
	alloc = ft_realloc((void **)strp, res + 1, res + 1 + BUFFER_SIZE);
	if (!alloc)
		return (-1);
	return (res);
}

ssize_t	add_substr(char **srcp, size_t src_len, size_t from, char **destp)
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
	ft_memmove(*destp + dest_len, *srcp + from + 1, src_len - from - 1);
	*(*destp + dest_len + src_len - from - 1) = '\0';
	alloc = ft_realloc((void **)srcp, src_len, from + 2);
	if (!alloc)
		return (-1);
	*(*srcp + from + 1) = '\0';
	return ((ssize_t)from + 1);
}

ssize_t	take_buf(char **strp, char **buf)
{
	size_t	i;
	size_t	alloc;

	alloc = ft_realloc((void **)strp, 0, 1);
	if (!alloc)
		return (-1);
	if (!*buf)
	{
		alloc = ft_realloc((void **)buf, 0, 1);
		if (!alloc)
			return (-1);
	}
	else if (!**buf)
		return (free_(buf), (ssize_t)ft_realloc((void **)strp, 1,
				BUFFER_SIZE + 1) - 1);
	i = 0;
	while (*(*buf + i) && *(*buf + i) != '\n')
		i++;
	return (load_substr(strp, buf, i));
}

ssize_t	load_substr(char **strp, char **buf, size_t nl)
{
	size_t	buf_len;
	size_t	alloc;

	buf_len = ft_strlen(*buf);
	alloc = ft_realloc((void **)strp, 1,
			nl + (nl != buf_len) + BUFFER_SIZE + 1);
	if (!alloc)
		return (-1);
	ft_memmove(*strp, *buf, nl + (nl != buf_len));
	if (buf_len == nl)
		return (free_(buf), (ssize_t)nl);
	ft_memmove(*buf, *buf + nl + 1, buf_len - nl - 1);
	alloc = ft_realloc((void **)buf, buf_len + 1, buf_len - nl);
	if (!alloc)
		return (-1);
	*(*buf + buf_len - nl - 1) = '\0';
	return ((ssize_t)nl + (nl != buf_len));
}
