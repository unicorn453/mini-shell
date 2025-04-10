/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 23:46:31 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/04/09 23:53:56 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	handle_pipe_case(t_cmd *cmd, char **envp, t_init *init)
{
	int	status;
	int	i;

	status = check_error_status(init->parsed_string, init->i, 258);
	if (status != 0)
	{
		cmd->pid[0] = -1;
		return (cmd->pid[1] = status, (void)0);
	}
	cmd->pipe = true;
	cmd->cmd[init->arg_index] = NULL;
	find_right_exec(cmd, init->parsed_string);
	init_def_cmd(cmd, envp, init->env_list);
	init->parsed_size = init->i;
	while (init->parsed_string[init->parsed_size] != NULL)
		init->parsed_size++;
	gc_untrack(cmd->cmd);
	cmd->cmd = gc_malloc(sizeof(char *) * (init->parsed_size + 1));
	check(cmd->cmd == NULL, 1);
	i = -1;
	while (++i < init->parsed_size)
		cmd->cmd[i] = NULL;
	cmd->pipe = true;
	init->arg_index = 0;
	init->i++;
}

void	ft_exec_pipes_parent(t_cmd *cmd, int fd_pipe[2], int *fd_in, pid_t pid)
{
	int	status;

	if (fd_pipe[1] != -1)
		close(fd_pipe[1]);
	if (!cmd->end_of_cmd)
	{
		if (fd_in[0] != -1)
			close(fd_in[0]);
		fd_in[0] = fd_pipe[0];
	}
	else
	{
		if (fd_pipe[0] != -1)
			close(fd_pipe[0]);
	}
	if (!cmd->heredoc)
		cmd->pid[cmd->index++] = pid;
	else
	{
		waitpid(pid, &status, 0);
		if (pipes()->heredoc_fd[0] != -1)
			close(pipes()->heredoc_fd[0]);
	}
}
