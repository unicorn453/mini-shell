/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:12:54 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/14 14:19:02 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	quote_parsing(char **tokens)
{
	int	i;
	
	i = -1;
	while (tokens[++i])
	{
		if (tokens[i][0] == '\'')
			tokens[i] = single_quote_handler(tokens[i]);
	// 	else if (tokens[i][0] == '\"')
	// 		tokens[i] = double_quotes_handler(tokens[i]);
	}
}

char	*single_quote_handler(char *token)
{
	int	i;

	char	*new_token;
	new_token = gc_malloc(ft_strlen(token) -1);
	if (new_token == NULL)
		return(perror("Minishell: memory allocation error"), NULL);
	i = 1;
	while (token[i] && token[i] != '\'')
	{
		new_token[i - 1] = token[i];
		i++;
	}
	new_token[i - 1] = '\0';
	return (new_token);
}

// char	*double_quotes_handler(char *token)
// {
	
// }
