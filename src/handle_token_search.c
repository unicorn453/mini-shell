/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_token_search.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:56:54 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/20 22:59:15 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

char	*handle_redir_in(int i, char **parsed_string, t_cmd *cmd)
{
	if (parsed_string[i + 1] != NULL)
	{
		cmd->redir_in = true;
		cmd->file_in = parsed_string[i + 1];
		return ("<");
	}
	return (NULL);
}

char	*handle_redir_out(int i, char **parsed_string, t_cmd *cmd)
{
	if (parsed_string[i + 1] != NULL)
	{
		cmd->redir_out = true;
		cmd->file_out = parsed_string[i + 1];
		return (">");
	}
	return (NULL);
}

char	*handle_redir_append(int i, char **parsed_string, t_cmd *cmd)
{
	if (parsed_string[i + 1] != NULL)
	{
		cmd->redir_append = true;
		cmd->file_out = parsed_string[i + 1];
		return (">>");
	}
	return (NULL);
}

char	*handle_heredoc_searching(int i, char **parsed_string, t_cmd *cmd)
{
	int	index;

	if (parsed_string[i + 1] != NULL)
	{
		index = find_last_heredoc(parsed_string, i);
		cmd->heredoc = true;
		cmd->delimiter = parsed_string[i + 1];
		cmd->last_heredoc = (index == i);
		return ("<<");
	}
	return (NULL);
}
