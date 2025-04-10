/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manage_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 16:35:27 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/10 16:47:46 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	dup_open_file(int *fd_in)
{
	if (fd_in[0] != -1)
		fd_in[0] = ft_in_out("file", 0);
	check(dup2(fd_in[0], STDIN_FILENO) == -1, 1);
}

int	ft_in_out(char *file, int mode)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(file, O_RDONLY);
		check(fd < 0, 1);
		if (fd < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
	}
	else if (mode == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		check(fd < 0, 1);
		if (fd < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
	}
	else
		fd = -1;
	return (fd);
}
