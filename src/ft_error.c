/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:19:51 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/28 19:38:58 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int find_last_heredoc(char **parsed_string, int i);

void check_error_status(char **parsed_string, int i)
{
    if (parsed_string[i + 1] == NULL)
    {
        const char *error_msg = "syntax error near unexpected token 'newline'\n";
        write(STDERR_FILENO, error_msg, strlen(error_msg));
        exit(2);
    }
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
        {
            index = i;
        }
        i++;
    }
    return index;
}

