/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:13:46 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/07 20:38:15 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

typedef struct s_cmd
{
	char	*delimiter;
	char	**cmd;
	char	**envp;
	bool	pipe;
	bool	redir_in;
	bool	redir_out;
	bool	redir_append;
	char	*file_in;
	char	*file_out;
	bool	end_of_cmd;
}			t_cmd;
void		exec_pipes(t_cmd *cmd, int *fd_in, bool last_child);
void		exec_cmd(char *cmd_path, char **cmd, char **envp);
void	init_cmd(t_cmd *cmd, char **envp)
{
	cmd->delimiter = NULL;
	cmd->cmd = malloc(sizeof(char *) * 2);
	cmd->cmd[0] = "/bin/cat";
	cmd->cmd[1] = NULL;
	cmd->envp = envp;
	cmd->pipe = true;
	cmd->redir_in = true;
	cmd->redir_out = false;
	cmd->redir_append = false;
	cmd->file_in = "input.txt";
	cmd->file_out = NULL;
	cmd->end_of_cmd = false;
}
void	init_second_cmd(t_cmd *cmd, char **envp)
{
	cmd->delimiter = NULL;
	cmd->cmd = malloc(sizeof(char *) * 3);
	cmd->cmd[0] = "/usr/bin/wc";
	cmd->cmd[1] = "-l";
	cmd->cmd[2] = NULL;
	cmd->envp = envp;
	cmd->pipe = true;
	cmd->redir_in = false;
	cmd->redir_out = true;
	cmd->redir_append = false;
	cmd->file_in = NULL;
	cmd->file_out = "output.txt";
	cmd->end_of_cmd = true;
}
int	ft_in_out(char *file, int mode)
{
	int	fd;

	if (mode == 0) // Read mode
	{
		fd = open(file, O_RDONLY);
		if (fd < 0)
		{
			perror("Error opening input file");
			return (-1);
		}
	}
	else if (mode == 1) // Write mode
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
void	exec_cmd(char *cmd_path, char **cmd, char **envp)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		fprintf(stderr, "Executing: %s\n", cmd_path);
		for (int i = 0; cmd[i] != NULL; i++)
			printf("Arg[%d]: %s\n", i, cmd[i]);
		if (execve(cmd_path, cmd, envp) == -1) // Ensure envp is passed
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
}
int	find_right_exec(t_cmd *cmd)
{
	static int fd_in = -1; // Ensure it persists across function calls
	printf("fd_in = %d\n", fd_in);
	if (cmd->pipe) // If it's part of a pipeline
	{
		exec_pipes(cmd, &fd_in, cmd->end_of_cmd);
		return (0);
	}
	else // If it's a standalone command
	{
		if (fd_in != -1) // If there's input from a previous pipe, use it
		{
			dup2(fd_in, 0);
			close(fd_in);
		}
		exec_cmd(cmd->cmd[0], cmd->cmd, cmd->envp);
		fd_in = -1; // Reset for future standalone commands
		return (0);
	}
	return (1);
}

void exec_pipes(t_cmd *cmd, int *fd_in, bool last_child)
{
    int fd_out;
    int fd_pipe[2];
    pid_t pid;
    int status;
    struct rusage usage;

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
        printf("Child: PID: %d\n", getpid());

        // Handle input redirection
        if (cmd->redir_in)
        {
            *fd_in = open(cmd->file_in, O_RDONLY);
            if (*fd_in < 0)
            {
                perror("Error opening input file");
                exit(EXIT_FAILURE);
            }
            dup2(*fd_in, 0);
            close(*fd_in);
        }
        else if (*fd_in != -1) // If previous command exists, read from pipe
        {
            dup2(*fd_in, 0);
            close(*fd_in); // Close only after duplicating
        }

        // Handle output redirection
        if (last_child && cmd->redir_out)
        {
            fd_out = open(cmd->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out != -1)
            {
                dup2(fd_out, 1);
                close(fd_out);
            }
        }
        else if (!last_child) // Send output to next process
        {
            dup2(fd_pipe[1], 1);
            close(fd_pipe[1]);
        }

        // Close pipes in the child process to prevent interference
        if(!last_child)
        close(fd_pipe[0]);

        // Execute command
        if (execve(cmd->cmd[0], cmd->cmd, cmd->envp) == -1)
        {
            perror("execve");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }
    else // Parent process
    {
        close(fd_pipe[1]); // Parent closes write end

        if (!last_child)
        {
            *fd_in = fd_pipe[0]; // Keep pipe open for the next command
        }
        else
        {
            printf("closing pipe\n");
            close(fd_pipe[0]); // Close it if it's the last command
        }

        waitpid(pid, &status, 0); // Wait for child process

        printf("Parent: Child finished, user CPU time: %ld sec\n",
               usage.ru_utime.tv_sec);
        printf("Parent: Child exit status: %d\n", WEXITSTATUS(status));
    }
}


int	main(int argc, char **argv, char **envp)
{
	t_cmd	cmd;
	int		command_done;

	command_done = -1;
	init_cmd(&cmd, envp);
	command_done = find_right_exec(&cmd);
	if (command_done == 0)
	{
		init_second_cmd(&cmd, envp);
		find_right_exec(&cmd);
	}
	return (0);
}
