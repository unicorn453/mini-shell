/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_util.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 20:44:59 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/04/10 19:48:35 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	close_open_fds(void)
{
	int	fd;

	fd = 3;
	while (fd < 10240)
	{
		if (fd >= 0)
			close(fd);
		fd++;
	}
}

void	gc_exit(int status)
{
	gc_free_all();
	exit(status);
}
