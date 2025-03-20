/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:32:50 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/20 23:09:30 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	initialize_command_structure(t_cmd *cmd, char **envp, t_init *init);
void	process_special_tokens(t_cmd *cmd, t_init *init);

void	init_def_cmd(t_cmd *cmd, char **envp, t_env **env_list)
{
	int	i;

	cmd->env_list = *env_list;
	cmd->delimiter = NULL;
	cmd->envp = envp;
	cmd->redir_in = false;
	cmd->redir_out = false;
	cmd->redir_append = false;
	cmd->pipe = false;
	cmd->end_of_cmd = false;
	cmd->file_in = NULL;
	cmd->file_out = NULL;
	cmd->heredoc = false;
	cmd->assigned_var = NULL;
	cmd->builtin = false;
	cmd->special_builtin = false;
	cmd->last_heredoc = false;
	cmd->heredoc_exists = false;
	cmd->heredoc_file = NULL;
	cmd->index = 0;
	i = -1;
	while (++i < MAX_PIPES)
		cmd->pid[i] = -2;
}

void execute_builtins_special(t_cmd *cmd, t_env **env_list)
{
	if (strcmp(cmd->cmd[0], "export") == 0 && cmd->assigned_var)
	{
		handle_export(env_list, cmd->assigned_var);
		cmd->pid[cmd->index++] = 0;
		return ;
	}
	else if (strcmp(cmd->cmd[0], "export") == 0 && !cmd->assigned_var)
	{
		print_env_reverse(env_list);
		cmd->pid[cmd->index++] = 0;
		return ;
	}
	else if (strcmp(cmd->cmd[0], "cd") == 0)
	{
		cd_test_call(cmd, env_list);
		cmd->pid[cmd->index++] = 0;
		return ;
	}
	else if (strcmp(cmd->cmd[0], "unset") == 0)
	{
		if (cmd->cmd[1])
			remove_env_var(env_list, cmd->cmd[1]);
		cmd->pid[cmd->index++] = 0;
		return ;
	}
	else if (strcmp(cmd->cmd[0], "exit") == 0)
		ft_run_exit(cmd);
	
cmd->pid[cmd->index++] = 0;
}

void	execute_builtins(t_cmd *cmd, t_env **env_list)
{
	pid_t	pid;
	int		fd_pipe[2];

	fd_pipe[0] = -1;
	fd_pipe[1] = -1;

	CHECK(!cmd->end_of_cmd && pipe(fd_pipe) == -1, 1);
	pid = fork();
	CHECK(pid < 0, 1);
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if ((strcmp(cmd->cmd[0], "echo") == 0 || strcmp(cmd->cmd[0],
					"/bin/echo") == 0) && cmd->cmd[1] != NULL)
		{
			echo_call_check(cmd, env_list);
			exit(0);
		}
		else if ((strcmp(cmd->cmd[0], "echo") == 0 || strcmp(cmd->cmd[0],
					"/bin/echo") == 0) && cmd->cmd[1] == NULL)
		{
			printf("\n");
			exit(0);
		}
		 if (strcmp(cmd->cmd[0], "pwd") == 0)
		{
			get_pwd();
			exit(0);
		}
		else if (strcmp(cmd->cmd[0], "env") == 0)
		{
			print_env_reverse(env_list);
			exit(0);
		}
		exit(1);
	}
	cmd->pid[cmd->index++] = pid;
}

void	init_cmd_stack(t_cmd *cmd, t_env **env_list, char **envp,
		char **parsed_string)
{
	t_init	init;

	init.parsed_string = parsed_string;
	init.env_list = env_list;
	initialize_command_structure(cmd, envp, &init);
	while (init.parsed_string[init.i] != NULL)
	{
		if (init.parsed_string[init.i] == NULL)
			break ;
		if (strcmp(init.parsed_string[init.i], "|") == 0
			&& in_quotes_or_not()->in_qoutes[init.i] == false)
		{
			handle_pipe_case(cmd, envp, &init);
			if (cmd->pid[0] == -1)
				return ;
			continue ;
		}
		if (ft_strchr(parsed_string[init.i], '=') != NULL)
			cmd->assigned_var = parsed_string[init.i];
		if (in_quotes_or_not()->in_qoutes[init.i] == false)
			process_special_tokens(cmd, &init);
		process_argument_in_cmd(cmd, envp, env_list, &init);
	}
	cmd->cmd[init.arg_index] = NULL;
	ft_ending_of_init(cmd, init.parsed_string, init.i);
}

void	initialize_command_structure(t_cmd *cmd, char **envp, t_init *init)
{
	init->i = 0;
	init->arg_index = 0;
	init->parsed_size = 0;
	while (init->parsed_string[init->parsed_size] != NULL)
		init->parsed_size++;
	cmd->cmd = gc_malloc(sizeof(char *) * (init->parsed_size + 1));
	CHECK(cmd->cmd == NULL, 1);
	cmd->cmd[init->parsed_size] = NULL;
	for (int j = 0; j <= init->parsed_size; j++)
		cmd->cmd[j] = NULL;
	init_def_cmd(cmd, envp, init->env_list);
}

void	process_special_tokens(t_cmd *cmd, t_init *init)
{
	char	*token;
	int		status;

	token = handle_token_search(init->i, init->parsed_string, cmd);
	if (token && strcmp(init->parsed_string[init->i], token) == 0)
	{
		if (strcmp(token, "=") != 0)
		{
			status = check_error_status(init->parsed_string, init->i, 258);
			if (status != 0)
			{
				cmd->pid[0] = -1;
				cmd->pid[1] = status;
				return ;
			}
			if (init->parsed_string[init->i + 1] && init->parsed_string[init->i
				+ 2])
			{
				init->i += 2;
				return ;
			}
		}
		else
		{
			init->i++;
			return ;
		}
	}
}
