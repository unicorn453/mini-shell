/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:19:51 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/17 16:41:53 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int find_last_heredoc(char **parsed_string, int i);

int check_error_status(char **parsed_string, int i, int status)
{
    if (parsed_string[i + 1] == NULL)
    {
        const char *error_msg = "syntax error near unexpected token 'newline'\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        return status;
    }
    else if (parsed_string[i + 1] != NULL && strcmp(parsed_string[i + 1], parsed_string[i]) == 0)
    {
        const char *error_msg = "syntax error near unexpected token '";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        write(STDERR_FILENO, parsed_string[i + 1], strlen(parsed_string[i + 1]));
        write(STDERR_FILENO, "'\n", 2);
        return status;
    }
    return 0;
}


char *handle_token_search(int i, char **parsed_string, t_cmd *cmd)
{
    if (strcmp(parsed_string[i], "<") == 0)
    {
        if (parsed_string[i + 1] != NULL)
        {
            cmd->redir_in = true;
            cmd->file_in = parsed_string[i + 1];
            return "<";
        }
    }
    else if (strcmp(parsed_string[i], ">") == 0)
    {
        if (parsed_string[i + 1] != NULL)
        {
            cmd->redir_out = true;
            cmd->file_out = parsed_string[i + 1];
            return ">";
        }
    }
    else if (strcmp(parsed_string[i], ">>") == 0)
    {
        if (parsed_string[i + 1] != NULL)
        {
            cmd->redir_append = true;
            cmd->file_out = parsed_string[i + 1];
            return ">>";
        }
    }
    else if (strcmp(parsed_string[i], "<<") == 0)
    {
        if (parsed_string[i + 1] != NULL)
        {
            int index = find_last_heredoc(parsed_string, i);
            if(index > i)
            {
            cmd->heredoc = true;
            cmd->delimiter = parsed_string[i + 1];
            cmd->last_heredoc = false;
            return "<<";
            } else if (index == i)
            {
                cmd->heredoc = true;
                cmd->delimiter = parsed_string[i + 1];
                cmd->last_heredoc = true;
                return "<<";
            }
        }
    }
    else if (ft_strchr(parsed_string[i], '=') != NULL)
    {
        cmd->assigned_var = parsed_string[i];
        return "=";
    }
    else 
    {
        return NULL;
    }
    return NULL;
}

int find_last_heredoc(char **parsed_string, int i)
{
    int index = i;
    while (parsed_string[i] != NULL)
    {
        if (strcmp(parsed_string[i], "<<") == 0)
            index = i;
        i++;
    }
    return index;
}
