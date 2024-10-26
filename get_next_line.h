/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehylee <jaehylee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 02:50:16 by jaehylee          #+#    #+#             */
/*   Updated: 2024/10/14 02:50:16 by jaehylee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size);

void	ft_memcpy(void *dest, const void *src, size_t n);

#endif
