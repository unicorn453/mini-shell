/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:05:54 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/09 18:25:27 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	env_len(t_env **env_list)
{
	// printf("head of node %s\n", (*env_list)->key);
	t_env	*temp;
	int		i = 0;

	if (!env_list || !*env_list)
		return (0);

	temp = *env_list;
	while (temp && temp->prev)
		temp = temp->prev;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}


void	print_env_reverse(t_env **env_list)
{
	t_env	*temp;

	if (!env_list || !*env_list)
		return ;
	temp = *env_list;
	while (temp->next)
		temp = temp->next;
	while (temp)
	{
		printf("%s=%s\n", temp->key, temp->value);
		temp = temp->prev;
	}
}
