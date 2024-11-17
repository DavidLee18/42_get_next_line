/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:50:16 by jaehylee          #+#    #+#             */
/*   Updated: 2024/11/16 21:51:44 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000000
# endif
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

size_t	ft_realloc(void **ptrp, size_t old_size, size_t new_size);

void	ft_memmove(void *dest, const void *src, size_t n);

char	*free_(char **p);

void	read_loop(int fd, char **strp, size_t offset, char **temp);

ssize_t	take_line(char **strp, size_t until, char **temp);

ssize_t	add_substr(char **srcp, size_t src_len, size_t from, char **destp);

ssize_t	take_temp(char **strp, char **temp);

ssize_t	load_substr(char **strp, char **temp, size_t nl);

size_t	ft_strlen(char *str);

#endif
