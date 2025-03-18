/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:13:46 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/18 19:36:37 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	find_right_exec(t_cmd *cmd, char **parsed_string)
{
	static int	fd_in = -1;
	int			original_stdin;
	int			original_stdout;

	original_stdin = dup(STDIN_FILENO);
	original_stdout = dup(STDOUT_FILENO);
	CHECK(original_stdin == -1, 1);
	CHECK(original_stdout == -1, 1);
	original_fds(original_stdin, original_stdout);
	if (cmd->pipe)
		return (exec_pipes(cmd, &fd_in, parsed_string), 0);
	else if (fd_in != -1)
	{
		dup2(fd_in, STDIN_FILENO);
		close(fd_in);
	}
	exec_cmd(cmd, &fd_in, cmd->end_of_cmd);
	fd_in = -1;
	dup2(original_fds(-1, -1)[0], STDIN_FILENO);
	close(original_fds(-1, -1)[0]);
	dup2(original_fds(-1, -1)[1], STDOUT_FILENO);
	close(original_fds(-1, -1)[1]);
	return (1);
}

void execute_command(t_cmd *cmd)
{
    char *error_msg;

    if (!cmd || !cmd->cmd || !cmd->cmd[0])
        return;

    // Ensure cmd->cmd is NULL-terminated
    int i = 0;
    while (cmd->cmd[i])
        i++;
    if (cmd->cmd[i] != NULL)  // Ensure NULL termination
        cmd->cmd[i] = NULL;

    if (execve(cmd->cmd[0], cmd->cmd, cmd->envp) == -1)
    {
        error_msg = ": command not found";
        write(STDERR_FILENO, "minishell: ", 11);
        write(STDERR_FILENO, cmd->cmd[0], ft_strlen(cmd->cmd[0]));
        write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
        write(STDERR_FILENO, "\n", 1);
        gc_free_all();
        exit(127);
    }
}


// void	execute_command(t_cmd *cmd)
// {
// 	char	*error_msg;

// 	if (cmd->cmd[0])
// 	{
// 		if (execve(cmd->cmd[0], cmd->cmd, cmd->envp) == -1)
// 		{
// 			error_msg = ": command not found";
// 			write(STDERR_FILENO, "minishell: ", 11);
// 			write(STDERR_FILENO, cmd->cmd[0], ft_strlen(cmd->cmd[0]));
// 			write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
// 			write(STDERR_FILENO, "\n", 1);
// 			gc_free_all();
// 			exit(127);
// 		}
// 	}
// }

void	exec_pipes(t_cmd *cmd, int *fd_in, char **parsed_string)
{
	pid_t	pid;
	int		heredoc_exist;

	init_pipes();
	CHECK(!cmd->end_of_cmd && pipe(pipes()->fd_pipe) == -1, 1);
	pid = fork();
	CHECK(pid < 0, 1);
	heredoc_exist = 0;
	heredoc_exist = ft_heredoc_exist(parsed_string);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		ft_exec_pipes_child_heredoc(cmd, pipes()->heredoc_fd, fd_in,
			heredoc_exist);
		ft_exec_pipes_child(cmd, fd_in, pipes()->fd_pipe, heredoc_exist);
		exit(EXIT_SUCCESS);
	}
	else
		ft_exec_pipes_parent(cmd, pipes()->fd_pipe, fd_in, pid);
}

int	wait_for_all_children(t_cmd *cmd)
{
	int	status;
	int	exit_status;
	int	i;

	if (cmd->pid[0] == -1)
		return (cmd->pid[1]);
	i = -1;
	while (++i < cmd->index)
	{
		if (cmd->pid[i] > 0)
		{
			waitpid(cmd->pid[i], &status, 0);
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
			{
				if (WTERMSIG(status) == 3)
					printf("Quit: 3\n");
				return (cmd->exit_status = 128 + WTERMSIG(status));
			}
		}
		else
			exit_status = 0;
	}
	return (cmd->index = 0, exit_status);
}
