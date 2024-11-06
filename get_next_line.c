/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:46:12 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/06 02:50:44 by jaehylee         ###   ########.fr       */
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

ssize_t	take_line(char **strp, char **buf)
{
	ssize_t	k;
	ssize_t	res;

	k = 0;
	while (*(*strp + k) && *(*strp + k) != '\n')
		k++;
	res = add_substr(strp, k, buf);
	if (res < BUFFER_SIZE)
		return (res);
	*strp = (char *)ft_realloc(*strp, res, res + BUFFER_SIZE);
	if (!*strp)
		return (0);
	return (BUFFER_SIZE);
}

ssize_t	add_substr(char **srcp, size_t from, char **destp)
{
	size_t	dest_len;
	size_t	src_len;

	src_len = ft_strlen(*srcp);
	if (from != 0 && from >= src_len)
		return (from);
	dest_len = ft_strlen(*destp);
	*destp = (char *)ft_realloc(*destp, dest_len + 1,
			dest_len + 2 + src_len - from);
	if (!*destp)
		return (-1);
	ft_memmove(*destp + dest_len, *srcp + from + 1, src_len - from + 1);
	*(*destp + dest_len + src_len - from + 1) = '\0';
	*srcp = ft_realloc(*srcp, src_len + 1, from + 1);
	*(*srcp + from + 1) = '\0';
	return ((ssize_t)from - (ssize_t)src_len);
}

ssize_t	take_buf(char **strp, char **buf)
{
	size_t	i;
	size_t	actual;

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
		return (-1);
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

	buf_len = ft_strlen(*buf);
	*strp = (char *)ft_realloc(*strp, 1, nl + 2);
	if (!*strp)
		return (-1);
	ft_memmove(*strp, *buf, nl + 1);
	if (!**strp && !**buf)
		return (0);
	*(*strp + nl + 1) = '\0';
	diff = buf_len - nl;
	ft_memmove(*buf, *buf + nl + 1, diff);
	*buf = (char *)ft_realloc(*buf, buf_len + 1, diff + 1);
	return (nl);
}
