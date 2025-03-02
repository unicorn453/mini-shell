/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:37:48 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/25 10:51:06 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd);
char	*str_join(char *saved, char *buffer);
char	*str_chr(const char *s, int c);
size_t	str_len(const char *s);
void	*ft_memcpy(void *dest, const void *src, size_t n);
// char	*ft_strdup(const char *s1);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif
