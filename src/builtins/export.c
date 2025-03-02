/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:00:22 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/01 16:43:22 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	handle_export(t_env **env_list, char *arg)
{
	char	*key;
	char	*value;
	char	*equal_sign;

	if (!arg || !*arg)
		return ;
	equal_sign = ft_strchr(arg, '=');
	if (equal_sign != NULL)
	{
		key = ft_substr(arg, 0, equal_sign - arg);
		value = ft_strdup(equal_sign + 1);
	}
	else
	{
		key = ft_strdup(arg);
		value = NULL;
	}
	if (!key)
		return (perror("Minishell: memory allocation error"));
	export_env_var(env_list, key, value);
}

void	export_env_var(t_env **env_list, char *key, char *value)
{
	t_env *temp;

	if (!key)
		return ;
	temp = *env_list;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(temp->key)) == 0)
		{
			if (value != NULL)
			{
				gc_untrack(temp->value);
				temp->value = ft_strdup(value);
				if (!temp->value)
					return (perror("Minishell: memory allocation error"));
				gc_track(temp->value);
			}
			free(key);
			return (free(value),(void)0);
		}
		temp = temp->next;
	}
	add_env_var(env_list, key, value);
	gc_track(key);
	gc_track(value);
}
