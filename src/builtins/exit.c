/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:10:23 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/16 15:07:36 by dtrendaf         ###   ########.fr       */
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
    gc_free_all();
    exit(exit_status);
}
