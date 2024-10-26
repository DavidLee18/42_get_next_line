/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 22:57:55 by jaehylee          #+#    #+#             */
/*   Updated: 2024/10/25 23:00:08 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_realloc(const void *ptr, size_t old_size, size_t new_size)
{
	void	*p;
	size_t	i;

	i = 0;
	p = malloc(new_size);
	if (!p)
		return (NULL);
	while (i < new_size)
	{
		((char *)p)[i] = 0;
		i++;
	}
	if (old_size < new_size)
		ft_memcpy(p, ptr, old_size);
	else
		ft_memcpy(p, ptr, new_size);
	return (p);
}

void	ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((char *) dest)[i] = ((char *)src)[i];
		i++;
	}
}
