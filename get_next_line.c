/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:46:12 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/11 01:52:20 by jaehylee         ###   ########.fr       */
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

ssize_t	take_line(char **strp, char **buf)
{
	ssize_t	k;
	ssize_t	res;
	size_t	alloc;

	if (!*buf)
	{
		*buf = (char *)malloc(1);
		if (!*buf)
			return (-1);
		**buf = '\0';
	}
	k = 0;
	if (!*strp)
		return (-1);
	while (*(*strp + k) && *(*strp + k) != '\n')
		k++;
	res = add_substr(strp, k, buf);
	if (res < BUFFER_SIZE)
		return (res);
	alloc = ft_realloc((void **)strp, res + 1, res + 1 + BUFFER_SIZE);
	if (!alloc)
		return (0);
	return (BUFFER_SIZE);
}

ssize_t	add_substr(char **srcp, size_t from, char **destp)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	alloc;

	if (!*srcp)
		return (-1);
	src_len = ft_strlen(*srcp);
	if (from != 0 && from >= src_len)
		return ((ssize_t)from);
	dest_len = ft_strlen(*destp);
	alloc = ft_realloc((void **)destp, dest_len + 1,
			dest_len + src_len - from);
	if (!alloc)
		return (-1);
	ft_memmove(*destp + dest_len, *srcp + from + 1, src_len - from - 1);
	*(*destp + dest_len + src_len - from - 1) = '\0';
	alloc = ft_realloc((void **)srcp, src_len + 1, from + 2);
	if (!alloc)
		return (-1);
	*(*srcp + from + 1) = '\0';
	return ((ssize_t)from - (ssize_t)src_len);
}

ssize_t	take_buf(char **strp, char **buf)
{
	size_t	i;
	ssize_t	actual;

	*strp = (char *)malloc(1);
	if (!*strp)
		return (-1);
	**strp = '\0';
	if (!*buf)
	{
		*buf = (char *)malloc(1);
		if (!*buf)
			return (-1);
		**buf = '\0';
	}
	else if (!**buf)
		return (free_(buf), -1);
	i = 0;
	while (*(*buf + i) && *(*buf + i) != '\n')
		i++;
	actual = load_substr(strp, buf, i);
	return (actual);
}

ssize_t	load_substr(char **strp, char **buf, size_t nl)
{
	size_t	buf_len;
	size_t	diff;
	size_t	alloc;

	buf_len = ft_strlen(*buf);
	alloc = ft_realloc((void **)strp, 1, nl + (nl != buf_len) + 1);
	if (!alloc)
		return (-1);
	ft_memmove(*strp, *buf, nl + (nl != buf_len));
	*(*strp + nl + (nl != buf_len)) = '\0';
	if (!**strp && !**buf)
		return (0);
	diff = buf_len - nl;
	ft_memmove(*buf, *buf + nl + 1, diff - 1);
	if (diff == 0)
		return (free_(buf), (ssize_t)nl);
	alloc = ft_realloc((void **)buf, buf_len + 1, diff);
	if (!alloc)
		return (-1);
	*(*buf + diff - 1) = '\0';
	return ((ssize_t)nl + 1);
}
