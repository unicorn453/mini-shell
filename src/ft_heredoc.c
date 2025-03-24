/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:44:05 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/20 18:34:42 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	create_heredoc_file(t_cmd *cmd, bool last_heredoc)
{
	int		my_out;
	char	tmp_filename[] = "file";

	my_out = -1;
	if ((!last_heredoc && !cmd->end_of_cmd) || (last_heredoc
			&& !cmd->end_of_cmd))
	{
		my_out = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (my_out == -1)
		{
			perror("Error creating heredoc file");
			exit(EXIT_FAILURE);
		}
		cmd->heredoc_file = strdup(tmp_filename);
	}
	return (my_out);
}

void	read_heredoc_input(t_cmd *cmd, int my_out, int *fd_out)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line || strcmp(line, cmd->delimiter) == 0)
		{
			if (line)
				free(line);
			break ;
		}
		if (!cmd->end_of_cmd)
		{
			CHECK((write(my_out, line, strlen(line)) == -1), 1);
			CHECK((write(my_out, "\n", 1) == -1), 1);
		}
		else
		{
			CHECK((write(*fd_out, line, strlen(line)) == -1), 1);
			CHECK((write(*fd_out, "\n", 1) == -1), 1);
		}
		if (line)
			free(line);
	}
}

int	handle_heredoc(t_cmd *cmd, int *fd_out, bool last_heredoc)
{
	int	my_out;

	CHECK(cmd->delimiter == NULL, 1);
	my_out = create_heredoc_file(cmd, last_heredoc);
	read_heredoc_input(cmd, my_out, fd_out);
	if (cmd->end_of_cmd || last_heredoc)
	{	
		if(my_out >= 0)
			close(my_out);
		unlink("file");
	}
	return (my_out);
}

int	check_for_redir(t_cmd *cmd, int file_fd)
{
	if ((cmd->redir_out || cmd->redir_append) && cmd->file_out)
	{
		file_fd = open(cmd->file_out,
				O_WRONLY | O_CREAT | (cmd->redir_append ? O_APPEND : O_TRUNC),
				0644);
		if (file_fd < 0)
		{
			perror("Error opening output file");
			exit(EXIT_FAILURE);
		}
	}
	return (file_fd);
}

int	ft_heredoc_check(t_cmd *cmd, int pipefd[2], bool last_child,
		bool last_heredoc)
{
	int	file_fd;

	(void)last_child;
	file_fd = -1;
	file_fd = check_for_redir(cmd, file_fd);
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	if (file_fd != -1)
		handle_heredoc(cmd, &file_fd, last_heredoc);
	else
		file_fd = handle_heredoc(cmd, &pipefd[1], last_heredoc);
	if(pipefd[1] >= 0)
		close(pipefd[1]);
	if (last_child && dup2(pipefd[0], STDIN_FILENO) == -1)
	{
		perror("dup2 failed for heredoc");
		exit(EXIT_FAILURE);
	}
	if(pipefd[1] >= 0)
		close(pipefd[0]);
	return (file_fd);
}
