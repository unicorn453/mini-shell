/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:32:50 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/12 16:06:28 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void init_def_cmd(t_cmd *cmd, char **envp)
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
}

void	print_stack(t_cmd stack)
{
	int i = 0;

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

#include "mini_shell.h"

void init_cmd_stack(t_cmd *cmd, char **envp, char **parsed_string)
{
    int i = 0, arg_index = 0;
    int command_done = -1;
    
    cmd->cmd = malloc(sizeof(char *) * 100);
    if (!cmd->cmd)
        return;
    while (parsed_string[i] != NULL)
    {
        if (strcmp(parsed_string[i], "|") == 0)
        {
            cmd->pipe = true;
            cmd->end_of_cmd = false;
            i++; 

            cmd->cmd[arg_index] = NULL;
            
            command_done = find_right_exec(cmd);

            if (command_done == 0)
            {
				init_def_cmd(cmd, envp);
                cmd->pipe = true;
                init_cmd_stack(cmd, envp, parsed_string + i);
            }
            return;
        }
        
        if (strcmp(parsed_string[i], "<") == 0)
        {
          if (parsed_string[i + 1] == NULL)  
    {
        const char *error_msg = "syntax error near unexpected token 'newline'\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(2);
    }
            if (parsed_string[i + 1])
            {
                cmd->redir_in = true;
                cmd->file_in = parsed_string[i + 1];
                i += 2;
                continue;
            }
        }
        else if (strcmp(parsed_string[i], ">") == 0)
        {
            if (parsed_string[i + 1] == NULL)  
    {
        const char *error_msg = "syntax error near unexpected token 'newline'\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(2);
    }
            if (parsed_string[i + 1])
            {
                cmd->redir_out = true;
                cmd->file_out = parsed_string[i + 1];
                i += 2;
                continue;
            }
        }
        else if (strcmp(parsed_string[i], ">>") == 0)
        {
            if (parsed_string[i + 1] == NULL)  
    {
        const char *error_msg = "syntax error near unexpected token 'newline'\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(2);
    }
            if (parsed_string[i + 1])
            {
                cmd->redir_append = true;
                cmd->file_out = parsed_string[i + 1];
                i += 2;
                continue;
            }
        }
        else if (strcmp(parsed_string[i], "<<") == 0)
        {
           if (parsed_string[i + 1] == NULL)  
    {
        const char *error_msg = "syntax error near unexpected token 'newline'\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(2);
    }
            if (parsed_string[i + 1])
            {
                cmd->heredoc = true;
                cmd->delimiter = parsed_string[i + 1];
                i += 2;
                continue;
            }
        }
        else
        {
            if (arg_index == 0)
                cmd->cmd[0] = find_command_path(parsed_string[i], envp);
            else
                cmd->cmd[arg_index] = parsed_string[i];

            arg_index++;
			cmd->cmd[arg_index] = NULL;
            i++;
        }
    }

    cmd->cmd[arg_index] = NULL;
fprintf(stderr, "cmd[0]: %s\n", cmd->cmd[0]);
    if (parsed_string[i] == NULL)
    {
        if (cmd->pipe == false)
            cmd->end_of_cmd = true;

        find_right_exec(cmd);
    }
}