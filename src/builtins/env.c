/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:05:54 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/10 17:35:12 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	env_len(t_env *env_list, int i)
{
	if (!env_list)
		return (i);
	return (env_len(env_list->next, i + 1));
}

void	print_export_reverse(t_env **env_list)
{
	t_env	*temp;

	if (!env_list || !*env_list)
		return ;
	temp = *env_list;
	while (temp->next)
		temp = temp->next;
	while (temp)
	{
		if (temp->key && temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		else if (temp->key && !temp->value)
			printf("%s\n", temp->key);
		temp = temp->prev;
	}
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
		if (temp->key && temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->prev;
	}
}
