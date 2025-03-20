/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:52:32 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/19 20:40:15 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	handle_pipe_case(t_cmd *cmd, char **envp, t_init *init)
{
	int	status;
	status = check_error_status(init->parsed_string, init->i, 258);
	if (status != 0)
	{
		cmd->pid[0] = -1;
		cmd->pid[1] = status;
		return ;
	}
	cmd->pipe = true;
	cmd->cmd[init->arg_index] = NULL;
	find_right_exec(cmd, init->parsed_string);
	init_def_cmd(cmd, envp, init->env_list);
	init->parsed_size = init->i;
	while (init->parsed_string[init->parsed_size] != NULL)
		init->parsed_size++;
	gc_untrack(cmd->cmd);
	cmd->cmd = gc_malloc(sizeof(char *) * (init->parsed_size + 1));
	cmd->cmd[init->parsed_size] = NULL;
	CHECK(cmd->cmd == NULL, 1);
	cmd->pipe = true;
	init->arg_index = 0;
	init->i++;
}

bool	not_a_special_charset(char *str, int index)
{
	if (in_quotes_or_not()->in_qoutes[index] == true)
		return (true);
	if (str == NULL)
		return (false);
	if (strcmp(str, "<<") == 0)
		return (false);
	 else if (strcmp(str, ">>") == 0)
		return (false);
	else if (strcmp(str, "|") == 0)
	 return (false);
	return (true);
}

void	process_argument_in_cmd(t_cmd *cmd, char **envp, t_env **env_list,
		t_init *init)
{
	if (init->arg_index == 0
		&& not_a_special_charset(init->parsed_string[init->i], init->i))
		{
			cmd->cmd[init->arg_index] = find_command_path(cmd, env_list,
					init->parsed_string[init->i], envp);
		}
	else if (init->arg_index != 0
		&& not_a_special_charset(init->parsed_string[init->i], init->i))
		{
			cmd->cmd[init->arg_index] = init->parsed_string[init->i];
		}
	init->arg_index++;
	if(strcmp(init->parsed_string[init->i], "|") != 0)
	init->i++;
}

void	ft_ending_of_init(t_cmd *cmd, char **parsed_string,
		int i)
{
	if (parsed_string[i] == NULL)
	{
		cmd->end_of_cmd = true;
			find_right_exec(cmd, parsed_string);
	}
}
