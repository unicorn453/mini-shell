/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:00:43 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/25 10:51:38 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"
// char	*ft_strdup(const char *s1)
// {
// 	size_t	size;
// 	char	*ptr;

// 	size = str_len(s1);
// 	ptr = malloc(size + 1);
// 	if (!ptr)
// 		return (NULL);
// 	ft_strlcpy(ptr, s1, size + 1);
// 	if (!ptr)
// 	{
// 		return (NULL);
// 	}
// 	return (ptr);
// }

static char	*extract_line(char **saved, int newline_index)
{
	char	*line;

	line = malloc(newline_index + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, *saved, newline_index);
	line[newline_index] = '\0';
	return (line);
}

static char	*update_saved(char **saved, int newline_index)
{
	char	*new_saved;

	new_saved = ft_strdup((*saved) + newline_index);
	if (!new_saved)
		return (NULL);
	free(*saved);
	*saved = new_saved;
	return (new_saved);
}

static char	*get_line(char **saved)
{
	int		newline_index;
	char	*line;

	if (!saved || !*saved || !**saved)
		return (NULL);
	newline_index = 0;
	while ((*saved)[newline_index] && (*saved)[newline_index] != '\n')
		newline_index++;
	if ((*saved)[newline_index] == '\n')
		newline_index++;
	line = extract_line(saved, newline_index);
	if (!line)
		return (free(*saved), *saved = NULL, NULL);
	if ((*saved)[newline_index] == '\0')
		return (free(*saved), *saved = NULL, line);
	if (!update_saved(saved, newline_index))
		return (free(line), free(*saved), *saved = NULL, NULL);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*saved;
	char		*buffer;
	int			read_bytes;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (free(saved), saved = NULL, NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(saved), saved = NULL, NULL);
	while (!str_chr(saved, '\n'))
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes < 0)
			return (free(buffer), free(saved), saved = NULL, NULL);
		if (read_bytes == 0)
			break ;
		buffer[read_bytes] = '\0';
		temp = str_join(saved, buffer);
		if (!temp)
			return (free(buffer), free(saved), saved = NULL, NULL);
		saved = temp;
	}
	free(buffer);
	return (get_line(&saved));
}
