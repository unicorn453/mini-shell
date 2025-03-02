/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:32:50 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/02 13:27:40 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	init_def_cmd(t_cmd *cmd, char **envp)
{
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
}

void	print_stack(t_cmd stack)
{
	int	i;

	i = 0;
	printf("Command: %s\n", stack.cmd[0]);
	while (stack.cmd[i] != NULL)
	{
		printf("Argument %d: %s\n", i, stack.cmd[i]);
		i++;
	}
	printf("End of command: %d\n", stack.end_of_cmd);
	printf("Redir in: %d\n", stack.redir_in);
	printf("Redir out: %d\n", stack.redir_out);
	printf("Redir append: %d\n", stack.redir_append);
	printf("File in: %s\n", stack.file_in);
	printf("File out: %s\n", stack.file_out);
	printf("Pipe: %d\n\n", stack.pipe);
}

void	init_cmd_stack(t_cmd *cmd, char **envp, char **parsed_string)
{
	int		i;
	int		arg_index;
	int		parsed_size;
	char	*token;

	i = 0;
	arg_index = 0;
	parsed_size = 0;
	while (parsed_string[parsed_size] != NULL)
		parsed_size++;
	cmd->cmd = gc_malloc(sizeof(char *) * 100);
	CHECK(cmd->cmd == NULL, 1);
	while (parsed_string[i] != NULL)
	{
		if (strcmp(parsed_string[i], "|") == 0)
		{
			cmd->pipe = true;
			i++;
			cmd->cmd[arg_index] = NULL;
			find_right_exec(cmd);
			init_def_cmd(cmd, envp);
			cmd->pipe = true;
			init_cmd_stack(cmd, envp, parsed_string + i);
			return ;
		}
		token = handle_token_search(i, parsed_string, cmd);
		if (token != NULL && strcmp(parsed_string[i], token) == 0)
		{
			check_error_status(parsed_string, i);
			if (parsed_string[i + 1])
			{
				i += 2;
				continue ;
			}
		}
		else
		{
			if (arg_index == 0)
				cmd->cmd[0] = find_command_path(parsed_string[i], envp);
			else
				cmd->cmd[arg_index] = parsed_string[i];
			arg_index++;
			i++;
		}
	}
	cmd->cmd[arg_index] = NULL;
	if (parsed_string[i] == NULL)
	{
		cmd->end_of_cmd = true;
		find_right_exec(cmd);
	}
}
