/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:44:05 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/05 11:04:05 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int handle_heredoc(t_cmd *cmd, int *fd_out, bool last_heredoc)
{
    char *line;
    int my_out = -1;

    if (cmd->delimiter == NULL)
    {
        perror("No delimiter found");
        exit(EXIT_FAILURE);
    }
 if (!last_heredoc && !cmd->end_of_cmd)
 {
    char tmp_filename[] = "file";
    my_out = open(tmp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (my_out == -1) 
    {
        perror("Error creating heredoc file");
        exit(EXIT_FAILURE);
    }
    cmd->heredoc_file = strdup(tmp_filename);
    
    if (my_out < 0)
    {
        perror("Error opening output file for heredoc");
        exit(EXIT_FAILURE);
    }
}
    while (1)
    {
        line = readline("> ");
        if (!line || strcmp(line, cmd->delimiter) == 0)
        {
            free(line);
            break;
        }

        if (!cmd->end_of_cmd)
        {
            if (write(my_out, line, strlen(line)) == -1 || write(my_out, "\n", 1) == -1)
            {
                perror("write failed");
                free(line);
                break;
            }
        }
        else 
        {
            if (write(*fd_out, line, strlen(line)) == -1 || write(*fd_out, "\n", 1) == -1)
            {
                perror("write failed");
                free(line);
                break;
            }
        }

        free(line);
    }

    if (cmd->end_of_cmd || last_heredoc)
        close(my_out);
        
        close(my_out);


    return my_out;
}



int ft_heredoc_check(t_cmd *cmd, int pipefd[2], bool last_child, bool last_heredoc)
{
    (void)last_child;
    int file_fd = -1;

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

    if (pipe(pipefd) == -1)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if (file_fd != -1)
        handle_heredoc(cmd, &file_fd, last_heredoc);
    else
       file_fd = handle_heredoc(cmd, &pipefd[1], last_heredoc);

    close(pipefd[1]);

    if (last_child && dup2(pipefd[0], STDIN_FILENO) == -1)
    {
        perror("dup2 failed for heredoc");
        exit(EXIT_FAILURE);
    }

    return file_fd;  
}
