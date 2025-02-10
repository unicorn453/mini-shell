/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:32:50 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/10 14:00:25 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"


void init_cmd_stack(t_cmd *cmd, char **envp, char **parsed_string)
{
    cmd->delimiter = NULL;
       cmd->cmd = malloc(sizeof(char *) * 3);
    cmd->envp = envp;
    // cmd->pipe = true;
    // cmd->redir_in = true;
    // cmd->redir_out = false;
    cmd->redir_append = false;
    // cmd->file_in = "input.txt";
    // cmd->file_out = NULL;
    cmd->end_of_cmd = true;
    int i = 0;
    int k = 0;
    char **cmd_with_flags;
    while(parsed_string[i] != NULL)
    {
        int j = 0;
       while(parsed_string[i][j] != '\0')
       {
        if(strcmp(parsed_string[i], "<") == 0)
        {
            cmd->redir_in = true;
            cmd->file_in = parsed_string[i + 1];
            i++;
        } else {
            cmd_with_flags = ft_split_plus(parsed_string[i], " \t\n");
            while(cmd_with_flags[k] != NULL)
            {
                if(k == 0)
                cmd->cmd[0] = find_command_path(cmd_with_flags[0], envp);
                else
                {
                    cmd->cmd[k] = cmd_with_flags[k];
                }
                k++;
                cmd->cmd[k] = NULL;
            }
        }
        i++;
        if(parsed_string[i] == NULL)
            cmd->end_of_cmd = true;
            else if (strcmp(parsed_string[i], "|") == 0)
            {
                cmd->pipe = true;
                cmd->end_of_cmd = false;
            }
            else if (strcmp(parsed_string[i], ">") == 0)
            {
                cmd->redir_out = true;
                cmd->file_out = parsed_string[i + 1];
                i++;
            }
       }
    }

}