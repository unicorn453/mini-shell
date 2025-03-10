/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:13:46 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/10 12:42:57 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int ft_in_out(char *file, int mode)
{
    int fd;

    if (mode == 0)
    {
        fd = open(file, O_RDONLY);
        // CHECK(fd < 0, 1);
        if (fd < 0)
        {
            perror("open failed");
            exit(EXIT_FAILURE);
        }
    }
    else if (mode == 1)
    {
        fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        // CHECK(fd < 0, 1, file);
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

void exec_cmd(t_cmd *cmd, int fd_in[1024], bool last_child)
{
    int pipefd[2];
    pid_t pid;

    CHECK(pipe(pipefd) == -1, 1);
    pid = fork();
    CHECK(pid < 0, 1);
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
            execute_command(cmd);
            exit(EXIT_SUCCESS);
        }
    }
    cmd->pid[cmd->index++] = pid;
    close(pipefd[1]);
    if (!last_child)
        fd_in[cmd->index] = pipefd[0];
}

int find_right_exec(t_cmd *cmd, char **parsed_string)
{
    static int fd_in = -1;
    static int fd_index = 0;
    if (cmd->pipe)
    {
        exec_pipes(cmd, &fd_in, &fd_index, parsed_string);
        return (0);
    }
    else
    {
        if (fd_in != -1)
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        exec_cmd(cmd, &fd_in, cmd->end_of_cmd);
        fd_in = -1;
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
            write(STDERR_FILENO, "minishell: ", 11);
            write(STDERR_FILENO, cmd->file_in, ft_strlen(cmd->file_in));
            write(STDERR_FILENO, ": ", 2);
            write(STDERR_FILENO, strerror(errno), ft_strlen(strerror(errno)));
            write(STDERR_FILENO, "\n", 1);
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
    if (cmd->redir_append)
        *fd_out = open(cmd->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
    else if (cmd->redir_out)
        *fd_out = open(cmd->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (cmd->redir_append || cmd->redir_out)
    {
        CHECK(*fd_out < 0, 1);
        CHECK(dup2(*fd_out, STDOUT_FILENO) == -1, 1);
        close(*fd_out);
    }
    else if (!last_child)
    {
        CHECK(dup2(fd_pipe[1], STDOUT_FILENO) == -1, 1);
        close(fd_pipe[1]);
    }
    if (!cmd->redir_append && !cmd->redir_out && !last_child)
        close(fd_pipe[0]);
}

void execute_command(t_cmd *cmd)
{
    if (execve(cmd->cmd[0], cmd->cmd, cmd->envp) == -1)
    {
        char *error_msg = ": command not found";
        write(STDERR_FILENO, "minishell: ", 11);
        write(STDERR_FILENO, cmd->cmd[0], ft_strlen(cmd->cmd[0]));
        write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
        write(STDERR_FILENO, "\n", 1);
        exit(127);
    }
}

bool ft_heredoc_exist(char **parsed_string)
{
    int i = 0;
    while (parsed_string[i] != NULL)
    {
        if (strcmp(parsed_string[i], "<<") == 0)
            return (1);
        i++;
    }
    return (0);
}

void exec_pipes(t_cmd *cmd, int fd_in[1024], int *fd_index, char **parsed_string)
{
    int fd_pipe[2];
    pid_t pid;
    int heredoc_fd[2];
    int status;
    (void)fd_index;

    CHECK(!cmd->end_of_cmd && pipe(fd_pipe) == -1, 1);

    pid = fork();
    CHECK(pid < 0, 1);
    int heredoc_exist = 0;
    heredoc_exist = ft_heredoc_exist(parsed_string);

    if (pid == 0)
    {
        if (cmd->heredoc)
        {
            ft_heredoc_check(cmd, heredoc_fd, cmd->end_of_cmd, cmd->last_heredoc);
            if (cmd->end_of_cmd)
            {
                execute_command(cmd);
                exit(EXIT_SUCCESS);
            }
        }
        if (heredoc_exist && !cmd->heredoc && cmd->redir_out)
        {
            int in = ft_in_out("file", 0);
            CHECK(in < 0, 1);
            dup2(in, STDIN_FILENO);
            close(in);
        }
        if (cmd->redir_in)
            handle_input_redirection(cmd, &fd_in[0]);
        else if (fd_in[0] != -1 && !cmd->heredoc && !heredoc_exist)
        {
            CHECK(dup2(fd_in[0], STDIN_FILENO) == -1, 1);
            close(fd_in[0]);
        }
        if (cmd->redir_out || cmd->redir_append)
        {
            handle_output_redirection(cmd, cmd->end_of_cmd, &fd_in[0], fd_pipe);
        }
        if (!cmd->end_of_cmd && !cmd->heredoc && !cmd->redir_out && !cmd->redir_append && !heredoc_exist)
            CHECK(dup2(fd_pipe[1], STDOUT_FILENO) == -1, 1);

        if (fd_pipe[0] != -1)
            close(fd_pipe[0]);
        if (fd_pipe[1] != -1)
            close(fd_pipe[1]);
        if (!cmd->heredoc)
        {
            if (heredoc_exist && cmd->redir_out)
            {
                execute_command(cmd);
            }
            else if (!heredoc_exist)
            {
                execute_command(cmd);
            }
            else if (heredoc_exist && cmd->end_of_cmd)
            {
                execute_command(cmd);
            }
        }
        exit(EXIT_SUCCESS);
    }
    else
    {
        close(fd_pipe[1]);

        if (!cmd->end_of_cmd)
        {
            close(fd_in[0]);
            fd_in[0] = fd_pipe[0];
        }
        else
            close(fd_pipe[0]);

        if (!cmd->heredoc)
            cmd->pid[cmd->index++] = pid;
        else
        {
            waitpid(pid, &status, 0);
            close(heredoc_fd[0]);
        }
    }
}

int wait_for_all_children(t_cmd *cmd)
{
    int status;
    int exit_status;
    for (int i = 0; i < cmd->index; i++)
    {
        if (cmd->pid[i] > 0) 
        {
            waitpid(cmd->pid[i], &status, 0);
            if (WIFEXITED(status))
            {
                exit_status = WEXITSTATUS(status);
            }
              //for exit with signals
        // if (WIFSIGNALED(status))
        // {
        //     int sig = WTERMSIG(status);
        //     printf("Child terminated by signal %d\n", sig);
        //     cmd->exit_status = 128 + sig; // Mimic Bash behavior
        // }
        }
        else if (cmd->pid[i] == 0)
            exit_status = 0;
    }
    cmd->index = 0;
    return (exit_status);
}
