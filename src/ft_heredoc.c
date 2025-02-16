/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:44:05 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/15 16:41:01 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void handle_heredoc(t_cmd *cmd, int *fd_out)
{
    if (cmd->heredoc)
    {
        if (cmd->delimiter == NULL)
        {
            perror("No delimiter found");
            exit(EXIT_FAILURE);
        }
        char *line;
        while (1)
        {
            line = readline("heredoc> ");
            if (line == NULL || strcmp(line, cmd->delimiter) == 0)
            {
                free(line);
                break;
            }
            if (write(*fd_out, line, strlen(line)) == -1 || write(*fd_out, "\n", 1) == -1)
            {
                perror("write failed");
                free(line);
                break;
            }
            free(line);
        }
        close(*fd_out);
    }
}
