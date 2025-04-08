/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 14:14:14 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/04/06 16:18:45 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*single_quote_handler(char *token, int *position)
{
	int		i;
	int		y;
	// int		count;
	char	*new_token;

	// count = 0;
	new_token = gc_malloc(ft_strlen(token) - 2 + 1);
	CHECK(new_token == NULL, 2);
	i = 0;
	y = -1;
	while (token[i] && token[i] != '\'')
		i++;
	if (token[i] == '\'')
	{
		i++;
		// count = 1;
		while (token[i] && token[i] != '\'')
			new_token[++y] = token[i++];
		if (token[i] == '\'')
		{
			// count = 2;
			*position = i;
		}
	}
	return (new_token[++y] = '\0', new_token);
}

char	*double_quotes_handler(t_env **env_list, char *token, int *position)
{
	int		i;
	int		y;
	char	*new_token;
	char	*expanded_token;

	(void)position;
	new_token = gc_malloc(ft_strlen(token) - 2 + 1);
	CHECK(new_token == NULL, 2);
	i = -1;
	y = -1;
	while (token[++i])
	{
		if (token[i] != '"')
			new_token[++y] = token[i];
	}
	new_token[++y] = '\0';
	gc_untrack(token);
	if (check_var(new_token) == false)
		return (new_token);
	expanded_token = handle_env_var(env_list, new_token);
	gc_untrack(new_token);
	if (expanded_token != NULL)
		new_token = expanded_token;
	return (new_token);
}

t_bool	*in_quotes_or_not(void)
{
	static t_bool	in_qoutes;

	return (&in_qoutes);
}

void	reset_quotes_array(void)
{
	int	i;

	i = -1;
	while (++i < 1024)
		in_quotes_or_not()->in_qoutes[i] = false;
}
