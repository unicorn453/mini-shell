/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_manage.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 10:24:11 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/08 20:22:31 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	ft_in_out(char *file, int mode)
{
	int	fd;

	if (mode == 0)
	{
		fd = open(file, O_RDONLY);
		check(fd < 0, 1);
		if (fd < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
	}
	else if (mode == 1)
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		check(fd < 0, 1);
		if (fd < 0)
		{
			perror("open failed");
			exit(EXIT_FAILURE);
		}
	}
	else
		fd = -1;
	return (fd);
}

void	handle_input_redirection(t_cmd *cmd, int *fd_in)
{
	if (cmd->redir_in)
	{
		if (*fd_in >= 0)
			close(*fd_in);
		*fd_in = open(cmd->file_in, O_RDONLY);
		if (*fd_in < 0)
		{
			write(STDERR_FILENO, "minishell: ", 11);
			write(STDERR_FILENO, cmd->file_in, ft_strlen(cmd->file_in));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
			write(STDERR_FILENO, "\n", 1);
			exit(EXIT_FAILURE);
		}
		dup2(*fd_in, STDIN_FILENO);
		if (*fd_in >= 0)
			close(*fd_in);
	}
	else if (*fd_in != -1)
	{
		dup2(*fd_in, STDIN_FILENO);
		if (*fd_in >= 0)
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
		check(*fd_out < 0, 1);
		check(dup2(*fd_out, STDOUT_FILENO) == -1, 1);
		close(*fd_out);
	}
	else if (!last_child)
	{
		check(dup2(fd_pipe[1], STDOUT_FILENO) == -1, 1);
		close(fd_pipe[1]);
	}
	if (!cmd->redir_append && !cmd->redir_out && !last_child)
		close(fd_pipe[0]);
}

int	*original_fds(int fd_in, int fd_out)
{
	static int	stdio[2] = {-111, -111};

	if (stdio[0] == -111)
	{
		stdio[0] = fd_in;
		stdio[1] = fd_out;
	}
	return (stdio);
}

void	execution(t_cmd *cmd)
{
	if (!cmd->builtin)
		execute_command(cmd);
	else
		execute_builtins(cmd, &cmd->env_list);
}
