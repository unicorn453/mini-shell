/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:13:46 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/28 19:46:14 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int ft_in_out(char *file, int mode)
{
    int fd;

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

void exec_cmd(t_cmd *cmd, int fd_in[1024], bool last_child)
{
    int pipefd[2];
    pid_t pid;

    (void)last_child;
    pid = fork();
    if (pid == 0)
    {
        if (cmd->heredoc)
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
            exit(EXIT_SUCCESS);
        }
        else
        {
            handle_input_redirection(cmd, &fd_in[0]);
            if (cmd->redir_out || cmd->redir_append)
            {
                handle_output_redirection(cmd, last_child, &fd_in[0], pipefd);
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

int find_right_exec(t_cmd *cmd)
{
    static int fd_in[1024];
    static int fd_index = 0;
    //  printf("fd: %d\n", fd_in[fd_index]);
    if (cmd->pipe)
    {
        exec_pipes(cmd, fd_in, &fd_index, cmd->end_of_cmd);
        return (0);
    }
    else
    {
        if (fd_index > 0)
        {
            fd_index--;
            dup2(fd_in[fd_index], STDIN_FILENO);
            close(fd_in[fd_index]);
            fd_in[fd_index] = -1;
        }
        exec_cmd(cmd, fd_in, cmd->end_of_cmd);
        return (0);
    }
    return (1);
}

void handle_input_redirection(t_cmd *cmd, int *fd_in)
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
        dup2(*fd_in, STDIN_FILENO);
        close(*fd_in);
    }
    else if (*fd_in != -1)
    {
        dup2(*fd_in, STDIN_FILENO);
        close(*fd_in);
    }
}

void handle_output_redirection(t_cmd *cmd, bool last_child, int *fd_out,
                               int fd_pipe[2])
{
    printf("fd_out: %d\n", *fd_out);
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

void execute_command(t_cmd *cmd)
{
    if (execve(cmd->cmd[0], cmd->cmd, cmd->envp) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
    return;
}
void exec_pipes(t_cmd *cmd, int fd_in[1024], int *fd_index, bool last_child)
{
    (void)fd_index;
    int fd_pipe[2];
    pid_t pid;
    int heredoc_fd[2];
    int status;

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

    if (pid == 0) // Child process
    {
        if (cmd->heredoc)
        {
            int heredo = ft_heredoc_check(cmd, heredoc_fd, last_child, cmd->last_heredoc);
            if (heredo != -1)
            {
                dup2(heredo, STDIN_FILENO);
                close(heredo);
            }
            fd_in[*fd_index] = heredo;
            // printf("fd_in[*fd_index]: %d\n", fd_in[*fd_index]);
        }
        // else if (cmd->redir_in)
        // {
        //     printf("nee dd\n");
            handle_input_redirection(cmd, &fd_in[*fd_index]);
        // }
        // printf("after else fd_in[*fd_index]: %d\n", fd_in[*fd_index]);
        if (cmd->redir_out || cmd->redir_append)
            handle_output_redirection(cmd, last_child, &fd_in[*fd_index], fd_pipe);
        if (last_child || !cmd->heredoc)
            execute_command(cmd); // Now correctly executes inside child process
        exit(EXIT_SUCCESS);
    }
    else // Parent process
    {
        if (!last_child)
        {
            close(fd_pipe[1]);             // Close write end in parent
            fd_in[*fd_index] = fd_pipe[0]; // Pass read end for next command
        }
        else
        {
            close(fd_pipe[0]); // No need for pipe in the last child
        }

        if (!cmd->heredoc)
        {
            cmd->pid[cmd->index++] = pid;
        }
        else
        {
            waitpid(pid, &status, 0);
            close(heredoc_fd[0]); // Close heredoc read end after process finishes
        }
    }
}

void wait_for_all_children(t_cmd *cmd)
{
    int status;

    for (int i = 0; i < cmd->index; i++)
    {
        if (cmd->pid[i] > 0)
            waitpid(cmd->pid[i], &status, 0);
    }
    cmd->index = 0;
}
