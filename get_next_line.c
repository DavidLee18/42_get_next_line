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
	static char		*temp;

	str = NULL;
	if (fd >= 0)
		read_loop(fd, &str, 0, &temp);
	return (str);
}

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

ssize_t	add_substr(char **srcp, const size_t src_len, const size_t from, char **destp)
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

ssize_t	take_temp(char **strp, char **temp)
{
	size_t	i;
	size_t	alloc;

	alloc = ft_realloc((void **)strp, 0, 1);
	if (!alloc)
		return (-1);
	if (!*temp)
	{
		alloc = ft_realloc((void **)temp, 0, 1);
		if (!alloc)
			return (-1);
	}
	else if (!**temp)
		return (free_(temp), (ssize_t)ft_realloc((void **)strp, 1,
				BUFFER_SIZE + 1) - 1);
	i = 0;
	while (*(*temp + i) && *(*temp + i) != '\n')
		i++;
	return (load_substr(strp, temp, i));
}

ssize_t	load_substr(char **strp, char **temp, const size_t nl)
{
	size_t	temp_len;
	size_t	alloc;

	temp_len = ft_strlen(*temp);
	alloc = ft_realloc((void **)strp, 1,
			nl + (nl != temp_len) + BUFFER_SIZE + 1);
	if (!alloc)
		return (-1);
	ft_memmove(*strp, *temp, nl + (nl != temp_len));
	if (temp_len == nl)
		return (free_(temp), (ssize_t)nl);
	ft_memmove(*temp, *temp + nl + 1, temp_len - nl - 1);
	alloc = ft_realloc((void **)temp, temp_len + 1, temp_len - nl);
	if (!alloc)
		return (-1);
	*(*temp + temp_len - nl - 1) = '\0';
	return ((ssize_t)nl + (nl != temp_len));
}
