/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:44:05 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/24 18:01:45 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void handle_heredoc(t_cmd *cmd, int *fd_out)
{
    int file_fd;
    char *line;
    char *g_line;

    if (cmd->heredoc)
    {
        if (cmd->delimiter == NULL)
        {
            perror("No delimiter found");
            exit(EXIT_FAILURE);
        }
        if (cmd->redir_in && cmd->file_in)
        {
            file_fd = open(cmd->file_in, O_RDONLY);
            if (file_fd < 0)
            {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }
            while ((g_line = get_next_line(file_fd)) != NULL)
            {
                write(*fd_out, g_line, strlen(g_line));
                free(g_line);
            }
            close(file_fd);
        }
        while (1)
        {
            line = readline("heredoc> ");
            if (line == NULL || strcmp(line, cmd->delimiter) == 0)
            {
                free(line);
                break;
            }

            if (write(*fd_out, line, strlen(line)) == -1 || write(*fd_out, "\n", 1) == -1)
            {
                perror("write failed");
                free(line);
                break;
            }
            free(line);
        }

        close(*fd_out);
    }
}

void ft_heredoc_check(t_cmd *cmd, int pipefd[2], int *fd_in, bool last_child)
{
    (void)last_child;
    (void)fd_in;
    int file_fd;
	char *line;

    if (cmd->redir_out && cmd->file_out)
    {
        file_fd = open(cmd->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (file_fd < 0)
        {
            perror("Error opening output file");
            exit(EXIT_FAILURE);
        }
    }

    if (cmd->heredoc)
    {
        if (pipe(pipefd) == -1)
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        handle_heredoc(cmd, &pipefd[1]);
        close(pipefd[1]);
			
		if(cmd->redir_in || cmd->redir_out)
		{
		while((line = get_next_line(pipefd[0])) != NULL)
		{
			if(!cmd->redir_out)
			write(STDOUT_FILENO, line, strlen(line));
			else
			write(file_fd, line, strlen(line));
			free(line);
		}
		close(file_fd);
		}
		dup2(pipefd[0], STDIN_FILENO);
			close(pipefd[0]);

        if (cmd->cmd[0] != NULL)
            execute_command(cmd);
    }
}
