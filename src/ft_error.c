/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 13:19:51 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/08 20:38:00 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int check_error_status(char **parsed_string, int i, int status)
{
    if (parsed_string[i + 1] == NULL)
    {
        write(STDERR_FILENO, "syntax error near unexpected token 'newline'\n", 45);
        return status;
    }
    else if (parsed_string[i + 1] != NULL && !not_a_special_charset(parsed_string[i + 1], i + 1))
    {
        write(STDERR_FILENO, "syntax error near unexpected token '", 36);
        write(STDERR_FILENO, parsed_string[i + 1], ft_strlen(parsed_string[i + 1]));
        write(STDERR_FILENO, "'\n", 2);
        return status;
    }
    return 0;
}

// char *handle_redir_in(int i, char **parsed_string, t_cmd *cmd) {
//     if (parsed_string[i + 1] != NULL) {
//         cmd->redir_in = true;
//         cmd->file_in = parsed_string[i + 1];
//         return "<";
//     }
//     return NULL;
// }

// char *handle_redir_out(int i, char **parsed_string, t_cmd *cmd) {
//     if (parsed_string[i + 1] != NULL) {
//         cmd->redir_out = true;
//         cmd->file_out = parsed_string[i + 1];
//         return ">";
//     }
//     return NULL;
// }

// char *handle_redir_append(int i, char **parsed_string, t_cmd *cmd) {
//     if (parsed_string[i + 1] != NULL) {
//         cmd->redir_append = true;
//         cmd->file_out = parsed_string[i + 1];
//         return ">>";
//     }
//     return NULL;
// }

// char *handle_heredoc_searching(int i, char **parsed_string, t_cmd *cmd) {
//     if (parsed_string[i + 1] != NULL) {
//         int index = find_last_heredoc(parsed_string, i);
//         cmd->heredoc = true;
//         cmd->delimiter = parsed_string[i + 1];
//         cmd->last_heredoc = (index == i);
//         return "<<";
//     }
//     return NULL;
// }

char *handle_token_search(int i, char **parsed_string, t_cmd *cmd) {
    if (ft_strcmp(parsed_string[i], "<") == 0)
        return handle_redir_in(i, parsed_string, cmd);
    else if (ft_strcmp(parsed_string[i], ">") == 0)
        return handle_redir_out(i, parsed_string, cmd);
    else if (ft_strcmp(parsed_string[i], ">>") == 0)
        return handle_redir_append(i, parsed_string, cmd);
    else if (ft_strcmp(parsed_string[i], "<<") == 0)
        return handle_heredoc_searching(i, parsed_string, cmd);
    
    return NULL;
}


int find_last_heredoc(char **parsed_string, int i)
{
    int index = i;
    while (parsed_string[i] != NULL)
    {
        if (ft_strcmp(parsed_string[i], "<<") == 0)
            index = i;
        i++;
    }
    return index;
}
