/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:46:12 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/05 10:45:39 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*str;
	static char		*buf;
	static _Bool	re;

	str = NULL;
	if (!re)
	{
		buf = (char *)malloc(1);
		if (!buf)
			return (NULL);
		*buf = '\0';
		re = 1;
	}
	read_loop(fd, &str, 0, &buf);
	return (str);
}

size_t	take_line(char **strp, char **buf, ssize_t len)
{
	size_t	k;
	ssize_t	res;

	k = 0;
	while (*strp[k] && *strp[k] != '\n')
		k++;
	res = add_substr(strp, k + 1, buf, len);
	if (res < BUFFER_SIZE)
		return (0);
	*strp = (char *)ft_realloc(*strp, len, len + BUFFER_SIZE);
	if (!*strp)
		return (0);
	return (BUFFER_SIZE);
}

ssize_t	add_substr(char **srcp, size_t from, char **destp, size_t len)
{
	size_t	dest_len;

	if (from == len)
		return (len);
	dest_len = 0;
	while (*destp[dest_len])
		dest_len++;
	*destp = (char *)ft_realloc(*destp, dest_len + 1,
			dest_len + 2 + len - from);
	if (!*destp)
		return (-1);
	ft_memmove(*destp, *srcp + from, len - from + 2);
	*srcp = ft_realloc(*srcp, len + 1, from + 1);
	return (from);
}

ssize_t	take_buf(char **strp, char **buf)
{
	size_t	i;
	size_t	actual;

	if (!**buf)
		return (0);
	i = 0;
	while (*buf[i] && *buf[i] != '\n')
		i++;
	actual = load_substr(strp, buf, i);
	return (actual - 1);
}

size_t	load_substr(char **strp, char **buf, size_t nl)
{
	size_t	buf_len;
	size_t	diff;

	buf_len = 0;
	while (*buf[buf_len])
		buf_len++;
	*strp = (char *)malloc(nl + 2);
	if (!*strp)
		return (0);
	ft_memmove(*strp, *buf, nl + 2);
	diff = buf_len - nl;
	ft_memmove(*buf, *buf + nl, diff + 1);
	*buf = (char *)ft_realloc(*buf, buf_len + 1, diff + 1);
	if (nl == buf_len)
		return (0);
	return (diff);
}
