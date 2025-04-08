/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_refiner_two.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:24:17 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/08 20:37:50 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	append_char(char **no_charse_str, char c)
{
	char	temp[2];
	char	*new_str;

	temp[0] = c;
	temp[1] = '\0';
	new_str = ft_strjoin(*no_charse_str, temp);
	check(new_str == NULL, 1);
	free(*no_charse_str);
	*no_charse_str = new_str;
}

void	init_process(t_process *process, char *token)
{
	process->start = 0;
	process->len = ft_strlen(token);
	process->no_charse_str = ft_strdup("");
	process->in_single = false;
	process->in_double = false;
}

void	process_token(char *token, char **charset, t_token **refined_tokens)
{
	t_process	*process;

	process = gc_malloc(sizeof(t_process));
	init_process(process, token);
	check(process->no_charse_str == NULL, 1);
	while (process->start < process->len)
	{
		handle_quotes(token[process->start], &process->in_single,
			&process->in_double);
		if (!process->in_single && !process->in_double)
		{
			process->op_len = check_for_operators(token, charset, process,
					refined_tokens);
			if (process->op_len > 0)
			{
				process->start += process->op_len;
				continue ;
			}
		}
		append_char(&process->no_charse_str, token[process->start]);
		process->start++;
	}
	if (*process->no_charse_str)
		append_token(refined_tokens, process->no_charse_str);
	free(process->no_charse_str);
}
