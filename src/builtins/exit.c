/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:10:23 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/18 16:10:57 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void ft_run_exit(t_cmd *cmd)
{
    int exit_status;
    exit_status = 0;
	if(cmd != NULL)
	{
    	if (cmd->cmd[1] != NULL)
    		exit_status = ft_atoi(cmd->cmd[1]);
	}
    close_open_fds();
    gc_free_all();
    exit(exit_status);
}
