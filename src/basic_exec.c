/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:13:46 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/11 14:42:37 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void        exec_pipes(t_cmd *cmd, int *fd_in, bool last_child);
void        exec_cmd(char *cmd_path, char **cmd, char **envp);


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

void    exec_cmd(char *cmd_path, char **cmd, char **envp)
{
    pid_t   pid;
    int     status;

    pid = fork();
    if (pid == 0)
    {
        if (execve(cmd_path, cmd, envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    }
    else if (pid < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
    exit(EXIT_SUCCESS);
}

int find_right_exec(t_cmd *cmd)
{
    static int  fd_in = -1;

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
        exec_cmd(cmd->cmd[0], cmd->cmd, cmd->envp);
        fd_in = -1;
        return (0);
    }
    return (1);
}

void    handle_input_redirection(t_cmd *cmd, int *fd_in)
{
    if (cmd->redir_in)
    {
		if(*fd_in != -1)
			close(*fd_in);
		fprintf(stderr, "file_in: %s\n", cmd->file_in);
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

void    handle_output_redirection(t_cmd *cmd, bool last_child, int *fd_out,
        int fd_pipe[2])
{
    if (cmd->redir_out)
    {
        *fd_out = open(cmd->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (*fd_out != -1)
        {
            dup2(*fd_out, 1);
            close(*fd_out);
        }
    }
    else if (!last_child)
    {
        dup2(fd_pipe[1], 1);
        close(fd_pipe[1]);
    }
    else if (last_child && cmd->redir_append)
    {
		printf("file_out:hh %s\n", cmd->file_out);
        *fd_out = open(cmd->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (*fd_out != -1)
        {
            dup2(*fd_out, 1);
            close(*fd_out);
        }
    }
    if (!last_child)
        close(fd_pipe[0]);
}

void    execute_command(t_cmd *cmd)
{
    if (execve(cmd->cmd[0], cmd->cmd, cmd->envp) == -1)
    {
        perror("execve");
        exit(EXIT_FAILURE);
    }
}

void    exec_pipes(t_cmd *cmd, int *fd_in, bool last_child)
{
    int     fd_out;
    int     fd_pipe[2];
    pid_t   pid;
    int     status;

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
        handle_output_redirection(cmd, last_child, &fd_out, fd_pipe);
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
        waitpid(pid, &status, 0);
    }
}

// int main(int argc, char **argv, char **envp)
// {
//     t_cmd   cmd;
//     int     command_done;


//     (void)argc;
//     (void)argv;
//     command_done = -1;
//     init_cmd(&cmd, envp);
//     command_done = find_right_exec(&cmd);
//     if (command_done == 0)
//     {
//         init_second_cmd(&cmd, envp);
//         find_right_exec(&cmd);
// 		command_done = 1;
//     }
// 	if (command_done == 1)
// 	{
// 		init_third_cmd(&cmd, envp);
// 		find_right_exec(&cmd);
// 	}
//     return (0);
// }
