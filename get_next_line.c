/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 01:46:12 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/17 14:59:00 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);
void	read_loop(const int fd, char **strp, size_t offset, char **temp);
ssize_t	take_temp(char **strp, char **temp);
ssize_t	load_substr(char **strp, char **temp, const size_t nl);
char	*free_(char **p);

char	*get_next_line(int fd)
{
	char		*str;
	static char	*temp;
	long long	buf_size;

	str = NULL;
	buf_size = BUFFER_SIZE;
	if (fd < 0 || buf_size <= 0 || buf_size > 9223372036854775807
		|| fd > 1048576)
		return (NULL);
	read_loop(fd, &str, 0, &temp);
	return (str);
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

char	*free_(char **p)
{
	if (*p)
	{
		free(*p);
		*p = NULL;
	}
	return (NULL);
}
