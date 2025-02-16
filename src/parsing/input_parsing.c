/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 19:12:54 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/15 15:33:42 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	quote_parsing(char **tokens)
{
	int	i;
	int y;
	
	i = -1;
	while (tokens[++i])
	{
		y = -1;
		while (tokens[i][++y])
		{
			if (tokens[i][y] == '\'')
			tokens[i] = single_quote_handler(tokens[i]);
			if (tokens[i] == NULL)
			{
				gc_free_all();
				exit(2);
			}
				
			// 	else if (tokens[i][0] == '\"')
	// 		tokens[i] = double_quotes_handler(tokens[i]);
		}
	}
}
static int count_chars(char *str,char c)
{
	int		i;
	
	i = 0;
	while (*str)
	{
		if (*str == c)
			i++;
		str++;
	}
	return (i);
}
char	*single_quote_handler(char *token)
{
	int		i;
	int		y;
	char	*new_token;
	
	i = count_chars(token, '\'');
	if ((i & 1) == 1)
		return(perror("Minishell: Error: unclosed, single qoute"), NULL);
	new_token = gc_malloc(ft_strlen(token) - i + 1);
	if (new_token == NULL)
		return(perror("Minishell: memory allocation error"), NULL);
	i = -1;
	y = -1;
	while (token[++i])
	{
		if (token[i] != '\'')
			new_token[++y] = token[i];
	}
	new_token[++y] = '\0';
	return (new_token);
}

// char	*double_quotes_handler(char *token)
// {
	
// }
