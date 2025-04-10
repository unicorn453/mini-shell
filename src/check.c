/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 15:22:45 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/10 17:41:48 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

inline void	check(int retval, int exit_code)
{
	if (retval != 0)
	{
		write(STDERR_FILENO, "minishell: ", 11);
		write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
		write(STDERR_FILENO, "\n", 1);
		gc_free_all();
		exit(exit_code);
	}
}
