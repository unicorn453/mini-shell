/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_refiner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 22:04:59 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/04/08 20:37:56 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

t_token	*new_token(char *value)
{
	t_token	*new;

	new = gc_malloc(sizeof(t_token));
	check(new == NULL, 1);
	new->value = ft_strdup(value);
	check(new->value == NULL, 1);
	gc_track(new->value);
	new->next = NULL;
	return (new);
}

void	append_token(t_token **head, char *value)
{
	t_token	*new;
	t_token	*temp;

	if (ft_strcmp(value, "\"\"") == 0 || ft_strcmp(value, "''") == 0)
		return ;
	new = new_token(value);
	if (*head == NULL)
		*head = new;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

void	handle_quotes(char current_char, bool *in_single, bool *in_double)
{
	if (current_char == '\'' && !(*in_double))
	{
		*in_single = !(*in_single);
	}
	else if (current_char == '"' && !(*in_single))
	{
		*in_double = !(*in_double);
	}
}

int	check_for_operators(char *str, char **charset, t_process *process,
		t_token **refined_tokens)
{
	int	j;
	int	op_len;

	j = 0;
	while (charset[j])
	{
		op_len = ft_strlen(charset[j]);
		if (ft_strncmp(&str[process->start], charset[j], op_len) == 0)
		{
			if (*(process->no_charse_str))
			{
				append_token(refined_tokens, process->no_charse_str);
				free(process->no_charse_str);
				process->no_charse_str = ft_strdup("");
				check(process->no_charse_str == NULL, 1);
			}
			append_token(refined_tokens, charset[j]);
			return (op_len);
		}
		j++;
	}
	return (0);
}

void	split_tokens(char **tokens, t_token **refined_tokens)
{
	static char	*charset[] = {"<<", "<", ">>", ">", "|", NULL};
	int			i;

	i = 0;
	while (tokens[i])
	{
		process_token(tokens[i], charset, refined_tokens);
		i++;
	}
}
