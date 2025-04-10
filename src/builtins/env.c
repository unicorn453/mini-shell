/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:05:54 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/10 16:54:11 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int	env_len(t_env **env_list)
{
	t_env	*temp;
	int		i;

	i = 0;
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
