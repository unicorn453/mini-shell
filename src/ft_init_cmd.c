/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:32:50 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/05 10:55:25 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void ft_ending_of_init(t_cmd *cmd, t_env **env_list, char **parsed_string, int i);

void init_def_cmd(t_cmd *cmd, char **envp, t_env **env_list)
{
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
	cmd->last_heredoc = false;
	cmd->heredoc_exists = false;
	cmd->heredoc_file = NULL;
	cmd->index = 0;
}

void print_stack(t_cmd stack)
{
    int i = 0;

    if (stack.cmd && stack.cmd[0])
    {
        printf("Command: %s\n", stack.cmd[0]);
        while (stack.cmd[i] != NULL)
        {
            printf("Argument %d: %s\n", i, stack.cmd[i]);
            i++;
        }
    }

    if (stack.end_of_cmd)
        printf("End of command: %d\n", stack.end_of_cmd);
    if (stack.redir_in)
        printf("Redir in: %d\n", stack.redir_in);
    if (stack.redir_out)
        printf("Redir out: %d\n", stack.redir_out);
    if (stack.redir_append)
        printf("Redir append: %d\n", stack.redir_append);
    if (stack.file_in)
        printf("File in: %s\n", stack.file_in);
    if (stack.file_out)
        printf("File out: %s\n", stack.file_out);
    if (stack.pipe)
        printf("Pipe: %d\n", stack.pipe);
    if (stack.heredoc)
        printf("Heredoc: %d\n", stack.heredoc);
    if (stack.assigned_var)
        printf("Assigned var: %s\n", stack.assigned_var);
    if (stack.builtin)
        printf("Builtin: %d\n", stack.builtin);
    if (stack.last_heredoc)
        printf("Last heredoc: %d\n", stack.last_heredoc);
    if (stack.heredoc_exists)
        printf("Heredoc exists: %d\n", stack.heredoc_exists);
    if (stack.heredoc_file)
        printf("Heredoc file: %s\n", stack.heredoc_file);
    if (stack.index)
        printf("Index: %d\n", stack.index);
    if (stack.delimiter)
        printf("Delimiter: %s\n", stack.delimiter);

    printf("\n");
}

void print_envlist(t_env **env_list)
{
	t_env *temp = *env_list;
	while (temp)
	{
		printf("Key: %s\n", temp->key);
		printf("Value: %s\n", temp->value);
		temp = temp->next;
	}
}

void init_cmd_stack(t_cmd *cmd, t_env **env_list, char **envp, char **parsed_string)
{
    int i = 0, arg_index = 0, parsed_size = 0;
    char *token;

    init_def_cmd(cmd, envp, env_list);
    
    while (parsed_string[parsed_size] != NULL)
        parsed_size++;

    cmd->cmd = gc_malloc(sizeof(char *) * (parsed_size + 1));
    CHECK(cmd->cmd == NULL, 1);

    while (parsed_string[i] != NULL)
    {
        if (strcmp(parsed_string[i], "|") == 0)
        {
            cmd->pipe = true;
            cmd->cmd[arg_index] = NULL;
            find_right_exec(cmd, parsed_string);
            init_def_cmd(cmd, envp, env_list);
            parsed_size -= i;
            cmd->cmd = gc_malloc(sizeof(char *) * (parsed_size + 1));
            cmd->pipe = true;
            arg_index = 0;
            i++;
            continue;
        }

        token = handle_token_search(i, parsed_string, cmd);
        if (token && strcmp(parsed_string[i], token) == 0)
        {
            if (strcmp(token, "=") != 0)
            {
                check_error_status(parsed_string, i);
                if (parsed_string[i + 1])
                {
                    i += 2;
                    continue;
                }
            }
            else
            {
                i++;
                continue;
            }
        }
        else
        {
            if (arg_index == 0)
                cmd->cmd[arg_index] = find_command_path(cmd, env_list, parsed_string[i], envp);
            else
                cmd->cmd[arg_index] = parsed_string[i];

            arg_index++;
            i++;
        }
    }

    cmd->cmd[arg_index] = NULL;
    ft_ending_of_init(cmd, env_list, parsed_string, i);
}


void ft_ending_of_init(t_cmd *cmd, t_env **env_list, char **parsed_string, int i)
{
    if (parsed_string[i] == NULL)
    {
        cmd->end_of_cmd = true;

        if (cmd->assigned_var)
        {
            if (check_builtins(env_list, cmd, cmd->cmd[0]))
            {
                handle_export(env_list, cmd->assigned_var);
            }
            return;
        }
        
        if (cmd->builtin)
            return;
        
        if (cmd->pipe)
        {
            find_right_exec(cmd, parsed_string);
        }
    }
}