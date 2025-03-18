/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_cmd_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:07:13 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/18 19:29:44 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	init_pipes(void)
{
	pipes()->fd_pipe[0] = -1;
	pipes()->fd_pipe[1] = -1;
	pipes()->heredoc_fd[0] = -1;
	pipes()->heredoc_fd[1] = -1;
}

void	ft_exec_pipes_child_heredoc(t_cmd *cmd, int heredoc_fd[2], int *fd_in,
		int heredoc_exist)
{
	int	in;

	if (cmd->heredoc)
	{
		ft_heredoc_check(cmd, heredoc_fd, cmd->end_of_cmd, cmd->last_heredoc);
		if (cmd->end_of_cmd)
			execute_command(cmd);
		if (cmd->end_of_cmd)
		{
			gc_free_all();
			exit(EXIT_SUCCESS);
		}
	}
	if (heredoc_exist && !cmd->heredoc && cmd->redir_out)
	{
		in = ft_in_out("file", 0);
		CHECK(in < 0, 1);
		dup2(in, STDIN_FILENO);
		close(in);
	}
	if (cmd->redir_in)
		handle_input_redirection(cmd, &fd_in[0]);
	else if (fd_in[0] != -1 && !cmd->heredoc && !heredoc_exist)
	{
		CHECK(dup2(fd_in[0], STDIN_FILENO) == -1, 1);
		if (fd_in[0] != -1)
			close(fd_in[0]);
	}
}

void	ft_exec_pipes_child(t_cmd *cmd, int *fd_in, int fd_pipe[2],
		int heredoc_exist)
{
	if (cmd->redir_out || cmd->redir_append)
	{
		handle_output_redirection(cmd, cmd->end_of_cmd, &fd_in[0], fd_pipe);
	}
	if (!cmd->end_of_cmd && !cmd->heredoc && !cmd->redir_out
		&& !cmd->redir_append && !heredoc_exist)
		CHECK(dup2(fd_pipe[1], STDOUT_FILENO) == -1, 1);
	if (fd_pipe[0] != -1)
		close(fd_pipe[0]);
	if (fd_pipe[1] != -1)
		close(fd_pipe[1]);
	if (!cmd->heredoc)
	{
		if (heredoc_exist && cmd->redir_out)
			execute_command(cmd);
		else if (!heredoc_exist)
			execute_command(cmd);
		else if (heredoc_exist && cmd->end_of_cmd)
			execute_command(cmd);
	}
}

t_pipe	*pipes(void)
{
	static t_pipe	pipe_info;

	return (&pipe_info);
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
