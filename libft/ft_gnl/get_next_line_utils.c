/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:00:51 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/14 14:25:34 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	str_len(const char *s)
{
	size_t	len;

	len = 0;
	while (s && s[len])
		len++;
	return (len);
}

char	*str_chr(const char *s, int c)
{
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	while (s && s[i])
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*str_join(char *saved, char *buffer)
{
	size_t	saved_len;
	size_t	buffer_len;
	char	*joined;

	saved_len = 0;
	if (saved)
	{
		saved_len = str_len(saved);
	}
	buffer_len = 0;
	if (buffer)
	{
		buffer_len = str_len(buffer);
	}
	joined = malloc(saved_len + buffer_len + 1);
	if (!joined)
		return (NULL);
	if (saved)
		ft_memcpy(joined, saved, saved_len);
	if (buffer)
		ft_memcpy(joined + saved_len, buffer, buffer_len);
	joined[saved_len + buffer_len] = '\0';
	free(saved);
	saved = NULL;
	return (joined);
}
