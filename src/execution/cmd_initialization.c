/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 12:52:32 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/09 23:46:55 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

bool	not_a_special_charset(char *str, int index)
{
	if (in_quotes_or_not()->in_qoutes[index] == true)
	{
		return (true);
	}
	if (str == NULL)
		return (false);
	if (ft_strcmp(str, "<<") == 0)
		return (false);
	if (ft_strcmp(str, "<") == 0)
		return (false);
	if (ft_strcmp(str, ">") == 0)
		return (false);
	else if (ft_strcmp(str, ">>") == 0)
		return (false);
	else if (ft_strcmp(str, "|") == 0)
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
	if (in_quotes_or_not()->in_qoutes[init->i]
		|| ft_strcmp(init->parsed_string[init->i], "|") != 0)
		init->i++;
}

void	ft_ending_of_init(t_cmd *cmd, char **parsed_string, int i)
{
	if (parsed_string[i] == NULL)
	{
		if (cmd->special_builtin)
		{
			if (cmd->cmd[0])
				execute_builtins_special(cmd, cmd->env_list);
			return ;
		}
		cmd->end_of_cmd = true;
		find_right_exec(cmd, parsed_string);
	}
}
