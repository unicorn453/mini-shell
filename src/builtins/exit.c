/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:10:23 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/09 19:35:13 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	ft_run_exit(t_cmd *cmd)
{
	int	exit_status;
	int	i;

	i = 0;
	while (cmd->cmd[i] != NULL)
		++i;
	exit_status = 0;
	if (cmd->pipe == true)
		return ;
	else if (i > 2)
	{
		write(STDERR_FILENO, "minishell: exit: too many arguments\n", 37);
		cmd->pid[0] = -1;
		cmd->pid[1] = 1;
		exit_status = 255;
		// return ;
	}
	else if (i == 2)
	{
		if (cmd->cmd[1] != NULL)
			exit_status = ft_atoi(cmd->cmd[1]);
	}
	gc_free_all();
	exit(exit_status);
}
