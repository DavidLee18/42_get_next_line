/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:50:16 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/01 00:57:53 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

void	ft_memmove(void *dest, const void *src, size_t n);

ssize_t	malloc_read(char **strp, int fd);

char	*free_(char *p);

#endif
