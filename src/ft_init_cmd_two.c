/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 19:36:09 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/10 16:11:34 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	run_builtin_child(t_cmd *cmd, t_env **env_list)
{
	signal(SIGINT, SIG_DFL);
	if ((ft_strcmp(cmd->cmd[0], "echo") == 0 || ft_strcmp(cmd->cmd[0],
				"/bin/echo") == 0))
	{
		if (cmd->cmd[1] != NULL)
			echo_call_check(cmd, env_list);
		else
			printf("\n");
		exit(0);
	}
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
	{
		get_pwd();
		exit(0);
	}
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
	{
		print_env_reverse(env_list);
		exit(0);
	}
	exit(1);
}

void	execute_builtins(t_cmd *cmd, t_env **env_list)
{
	pid_t	pid;
	int		fd_pipe[2];

	fd_pipe[0] = -1;
	fd_pipe[1] = -1;
	if (!cmd->end_of_cmd && pipe(fd_pipe) == -1)
		check(1, 1);
	pid = fork();
	check(pid < 0, 1);
	if (pid == 0)
		run_builtin_child(cmd, env_list);
	cmd->pid[cmd->index++] = pid;
}

void	execute_builtins_special(t_cmd *cmd, t_env **env_list)
{
	if (ft_strcmp(cmd->cmd[0], "export") == 0 && cmd->assigned_var)
		return (handle_export(env_list, cmd->assigned_var),
			cmd->pid[cmd->index++] = 0, (void)0);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0 && !cmd->assigned_var
		&& !cmd->cmd[1])
		return (print_export_reverse(env_list), cmd->pid[cmd->index++] = 0,
			(void)0);
	else
	{
		if (cmd->cmd[1])
			handle_export(env_list, cmd->cmd[1]);
	}
	if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (cd_test_call(cmd, env_list), cmd->pid[cmd->index++] = 0,
			(void)0);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
	{
		if (cmd->cmd[1])
			remove_env_var(env_list, cmd->cmd[1]);
		cmd->pid[cmd->index++] = 0;
		return ;
	}
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		ft_run_exit(cmd);
	cmd->pid[cmd->index++] = 0;
}
