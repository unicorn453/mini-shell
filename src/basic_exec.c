/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:13:46 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/15 16:40:51 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	exec_pipes(t_cmd *cmd, int *fd_in, bool last_child);
void	exec_cmd(t_cmd *cmd, int *fd_in, bool last_child);

int	ft_in_out(char *file, int mode)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			perror("Error opening input file");
			return (-1);
		}
	}
	else if (mode == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror("Error opening output file");
			return (-1);
		}
	}
	else
	{
		fd = -1;
	}
	return (fd);
}

void	ft_heredoc_check(t_cmd *cmd, int pipefd[2], int *fd_in, bool last_child)
{
	(void)last_child;
	if (cmd->heredoc)
	{
		if (pipe(pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		handle_heredoc(cmd, &pipefd[1]);
		close(pipefd[1]);
		if (cmd->redir_in)
			handle_input_redirection(cmd, fd_in);
		else
		{
			dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);
		}
		if (cmd->redir_out)
			handle_output_redirection(cmd, last_child, fd_in, pipefd);
		if (cmd->cmd[0] != NULL)
			execute_command(cmd);
	}
}

void	exec_cmd(t_cmd *cmd, int *fd_in, bool last_child)
{
	int		pipefd[2];
	pid_t	pid;

	(void)last_child;
	pid = fork();
	if (pid == 0)
	{
		if (cmd->heredoc)
		{
			ft_heredoc_check(cmd, pipefd, fd_in, last_child);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		else
		{
			handle_input_redirection(cmd, fd_in);
			if (cmd->redir_out || cmd->redir_append)
			{
				handle_output_redirection(cmd, last_child, fd_in, pipefd);
			}
			execute_command(cmd);
			printf("Executed command\n");
			exit(EXIT_SUCCESS);
		}
		exit(EXIT_SUCCESS);
	}
	else if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	cmd->pid[cmd->index++] = pid;
}

int	find_right_exec(t_cmd *cmd)
{
	static int	fd_in = -1;

	if (cmd->pipe)
	{
		exec_pipes(cmd, &fd_in, cmd->end_of_cmd);
		return (0);
	}
	else
	{
		if (fd_in != -1)
		{
			dup2(fd_in, 0);
			close(fd_in);
		}
		exec_cmd(cmd, &fd_in, cmd->end_of_cmd);
		fd_in = -1;
		return (0);
	}
	return (1);
}

void	handle_input_redirection(t_cmd *cmd, int *fd_in)
{
	if (cmd->redir_in)
	{
		if (*fd_in != -1)
			close(*fd_in);
		*fd_in = open(cmd->file_in, O_RDONLY);
		if (*fd_in < 0)
		{
			perror("Error opening input file");
			exit(EXIT_FAILURE);
		}
		dup2(*fd_in, 0);
		close(*fd_in);
	}
	else if (*fd_in != -1)
	{
		dup2(*fd_in, 0);
		close(*fd_in);
	}
}

void	handle_output_redirection(t_cmd *cmd, bool last_child, int *fd_out,
		int fd_pipe[2])
{
	if (cmd->redir_append)
		*fd_out = open(cmd->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (cmd->redir_out)
		*fd_out = open(cmd->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->redir_append || cmd->redir_out)
	{
		if (*fd_out != -1)
		{
			if (dup2(*fd_out, STDOUT_FILENO) == -1)
			{
				perror("dup2 output redirection");
				exit(EXIT_FAILURE);
			}
			close(*fd_out);
		}
		else
		{
			perror("open file for redirection");
			exit(EXIT_FAILURE);
		}
	}
	else if (!last_child)
	{
		if (dup2(fd_pipe[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 pipe output");
			exit(EXIT_FAILURE);
		}
		close(fd_pipe[1]);
	}
	if (!cmd->redir_append && !cmd->redir_out && !last_child)
		close(fd_pipe[0]);
}

void	execute_command(t_cmd *cmd)
{

	if (execve(cmd->cmd[0], cmd->cmd, cmd->envp) == -1)
	{
		perror("execve");
		exit(EXIT_FAILURE);
	}
	return ;
}

void	exec_pipes(t_cmd *cmd, int *fd_in, bool last_child)
{
	int		fd_pipe[2];
	pid_t	pid;

	if (!last_child && pipe(fd_pipe) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		handle_input_redirection(cmd, fd_in);
		handle_output_redirection(cmd, last_child, fd_in, fd_pipe);
		// ft_heredoc_check(cmd, fd_pipe, fd_in, last_child);
		execute_command(cmd);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd_pipe[1]);
		if (!last_child)
			*fd_in = fd_pipe[0];
		else
			close(fd_pipe[0]);
		cmd->pid[cmd->index++] = pid;
	}
}

void	wait_for_all_children(t_cmd *cmd)
{
	int	status;

	for (int i = 0; i < cmd->index; i++)
	{
		if (cmd->pid[i] > 0)
			waitpid(cmd->pid[i], &status, 0);
	}
	cmd->index = 0;
}
