/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:46:12 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/05 04:21:07 by jaehylee         ###   ########.fr       */
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

size_t	take_line(char **strp, size_t offset, char **buf, ssize_t len)
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
