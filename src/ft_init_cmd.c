/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:32:50 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/08 21:06:20 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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

void	init_cmd_stack(t_cmd *cmd, t_env **env_list, char **envp,
		char **parsed_string)
{
	t_init	init;

	init.parsed_string = parsed_string;
	init.env_list = env_list;
	initialize_command_structure(cmd, envp, &init);
	while (init.parsed_string[init.i] != NULL)
	{
		if (ft_strcmp(init.parsed_string[init.i], "|") == 0
			&& in_quotes_or_not()->in_qoutes[init.i] == false)
		{
			handle_pipe_case(cmd, envp, &init);
			if (cmd->pid[0] == -1)
				return ;
			continue ;
		}
		if (ft_strchr(parsed_string[init.i], '=') != NULL)
			cmd->assigned_var = parsed_string[init.i];
		if (in_quotes_or_not()->in_qoutes[init.i] == false
			&& process_special_tokens(cmd, &init) == -1)
			return ;
		process_argument_in_cmd(cmd, envp, env_list, &init);
	}
	cmd->cmd[init.arg_index] = NULL;
	ft_ending_of_init(cmd, init.parsed_string, init.i);
}

void	initialize_command_structure(t_cmd *cmd, char **envp, t_init *init)
{
	int	j;

	j = -1;
	init->i = 0;
	init->arg_index = 0;
	init->parsed_size = 0;
	while (init->parsed_string[init->parsed_size] != NULL)
		init->parsed_size++;
	cmd->cmd = gc_malloc(sizeof(char *) * (init->parsed_size + 1));
	check(cmd->cmd == NULL, 1);
	cmd->cmd[init->parsed_size] = NULL;
	while (++j <= init->parsed_size)
		cmd->cmd[j] = NULL;
	init_def_cmd(cmd, envp, init->env_list);
}

int	process_special_tokens(t_cmd *cmd, t_init *init)
{
	char	*token;
	int		status;

	token = handle_token_search(init->i, init->parsed_string, cmd);
	if (token && ft_strcmp(init->parsed_string[init->i], token) == 0)
	{
		if (ft_strcmp(token, "=") != 0)
		{
			status = check_error_status(init->parsed_string, init->i, 258);
			if (status != 0)
			{
				cmd->pid[0] = -1;
				cmd->pid[1] = status;
				return (-1);
			}
			if (init->parsed_string[init->i + 1] && init->parsed_string[init->i
					+ 2])
				return (init->i += 2, 0);
		}
		else
			return (init->i++, 0);
	}
	return (0);
}
