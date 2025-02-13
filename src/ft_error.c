/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:19:51 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/13 17:38:23 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

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
            cmd->heredoc = true;
            cmd->delimiter = parsed_string[i + 1];
            return "<<";
        }
    }
    else 
    {
        return NULL;
    }
    return NULL;
}
