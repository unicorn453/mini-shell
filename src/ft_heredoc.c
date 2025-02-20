/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 16:44:05 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/13 17:38:22 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	handle_heredoc(t_cmd *cmd, int *fd_out)
{
	int		file_fd;
	char	*line;

	if (cmd->heredoc)
	{
		if (cmd->delimiter == NULL)
		{
			perror("No delimiter found");
			exit(EXIT_FAILURE);
		}
		// If `< file` exists, read it first
		if (cmd->redir_in && cmd->file_in)
		{
			file_fd = open(cmd->file_in, O_RDONLY);
			if (file_fd < 0)
			{
				perror("Error opening input file");
				exit(EXIT_FAILURE);
			}
			while ((line = get_next_line(file_fd)) != NULL)
			{
				write(STDOUT_FILENO, line, strlen(line));
				write(STDOUT_FILENO, "\n", 1);
				free(line);
			}
			// while ((line = get_next_line(file_fd)) != NULL)
			// {
			// 	write(*fd_out, line, strlen(line));
			// 	// fd_out instead of stdout
			// 	write(*fd_out, "\n", 1);
			// 	free(line);
			// }
			close(file_fd);
		}
		while (1)
		{
			line = readline("heredoc> ");
			if (line == NULL || strcmp(line, cmd->delimiter) == 0)
			{
				free(line);
				break ;
			}
			if (write(*fd_out, line, strlen(line)) == -1 || write(*fd_out, "\n",
					1) == -1)
			{
				perror("write failed");
				free(line);
				break ;
			}
			free(line);
		}
		close(*fd_out);
	}
}
