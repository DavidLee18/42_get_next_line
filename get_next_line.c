/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:46:12 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/05 20:29:54 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*str;
	static char		*buf;

	str = NULL;
	read_loop(fd, &str, 0, &buf);
	return (str);
}

ssize_t	take_line(char **strp, char **buf, ssize_t len)
{
	ssize_t	k;
	ssize_t	res;

	k = 0;
	while (*(*strp + k) && *(*strp + k) != '\n')
		k++;
	if (k == len)
		k = -1;
	res = add_substr(strp, k + 1, buf, len);
	if (res < BUFFER_SIZE)
		return (res);
	*strp = (char *)ft_realloc(*strp, len, len + BUFFER_SIZE);
	if (!*strp)
		return (0);
	return (BUFFER_SIZE);
}

ssize_t	add_substr(char **srcp, size_t from, char **destp, size_t len)
{
	size_t	dest_len;

	if (from == 0)
	{
		*srcp = (char *)malloc(1);
		if (*srcp)
			**srcp = '\0';
		return (-1);
	}
	if (from == len)
		return (len);
	dest_len = 0;
	while (*(*destp + dest_len))
		dest_len++;
	*destp = (char *)ft_realloc(*destp, dest_len + 1,
			1 + len - from);
	if (!*destp)
		return (-1);
	ft_memmove(*destp, *srcp + from, len - from);
	*(*destp + len - from + 1) = '\0';
	*srcp = ft_realloc(*srcp, len + 1, from + 1);
	*(*srcp + from) = '\0';
	return (from);
}

ssize_t	take_buf(char **strp, char **buf)
{
	size_t	i;
	size_t	actual;

	if (!*buf)
	{
		*buf = (char *)malloc(1);
		if (!*buf)
			return (-1);
		**buf = '\0';
	}
	else if (!**buf)
		return (0);
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

	buf_len = 0;
	while (*(*buf + buf_len))
		buf_len++;
	*strp = (char *)malloc(nl + 2);
	if (!*strp)
		return (-1);
	ft_memmove(*strp, *buf, nl + 1);
	if (!**strp && !**buf)
		return (0);
	*(*strp + nl + 1) = '\0';
	diff = buf_len - nl;
	ft_memmove(*buf, *buf + nl, diff + 1);
	*buf = (char *)ft_realloc(*buf, buf_len + 1, diff + 1);
	return (nl + 1);
}
