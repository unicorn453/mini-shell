/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 09:11:20 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/17 16:39:40 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

bool	ft_heredoc_exist(char **parsed_string)
{
	int	i;

	i = 0;
	while (parsed_string[i] != NULL)
	{
		if (strcmp(parsed_string[i], "<<") == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exec_cmd_heredoc(t_cmd *cmd, int pipefd[2], int *fd_in, bool last_child)
{
	ft_heredoc_check(cmd, pipefd, last_child, cmd->last_heredoc);
	execute_command(cmd);
	close(pipefd[0]);
	if (!cmd->pipe)
		close(pipefd[1]);
	else
	{
		fd_in[cmd->index] = pipefd[1];
		close(pipefd[1]);
	}
	return (0);
}

int	exec_cmd_redir(t_cmd *cmd, int *fd_in, bool last_child, int pipefd[2])
{
	if (cmd->redir_in)
		handle_input_redirection(cmd, &fd_in[0]);
	if (cmd->redir_out || cmd->redir_append)
		handle_output_redirection(cmd, last_child, &fd_in[0], pipefd);
	else if (!last_child)
	{
		CHECK(dup2(pipefd[1], STDOUT_FILENO) == -1, 1);
		close(pipefd[1]);
	}
	if (!cmd->redir_append && !cmd->redir_out && !last_child)
		close(pipefd[0]);
	return (1);
}

int	exec_cmd_child(t_cmd *cmd, int *fd_in, bool last_child, int pipefd[2])
{
	if (cmd->heredoc)
		return (exec_cmd_heredoc(cmd, pipefd, fd_in, last_child));
	else
		return (exec_cmd_redir(cmd, fd_in, last_child, pipefd));
}

void	exec_cmd(t_cmd *cmd, int *fd_in, bool last_child)
{
	int		pipefd[2];
	pid_t	pid;
	int		exec_cmd;

	CHECK(pipe(pipefd) == -1, 1);
	pid = fork();
	CHECK(pid < 0, 1);
	exec_cmd = 0;
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		exec_cmd = exec_cmd_child(cmd, fd_in, last_child, pipefd);
		if (exec_cmd == 0)
			exit(EXIT_SUCCESS);
		else if (exec_cmd == 1)
		{
			if(!cmd->builtin)
			execute_command(cmd);
			else
			execute_builtins(cmd, &cmd->env_list);
			exit(EXIT_SUCCESS);
		}
	}
	cmd->pid[cmd->index++] = pid;
	close(pipefd[1]);
	if (!last_child)
		fd_in[cmd->index] = pipefd[0];
}
