/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:00:22 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/19 22:08:34 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void	handle_plus_equal(t_env **env_list, char *key, char *plus_eq,
	char **value)
{
char	*new_key;
char	*old_value;

new_key = ft_strjoin("$", key);
old_value = search_env_var(*env_list, new_key);
*value = ft_strjoin(old_value, plus_eq + 2);
free(new_key);
}

int	parse_export_argument(char *arg, char **key, char **value, t_env **env_list)
{
char	*equal_sign;
char	*plus_eq;

equal_sign = ft_strchr(arg, '=');
plus_eq = ft_strnstr(arg, "+=", ft_strlen(arg));
if (plus_eq && plus_eq == equal_sign - 1)
{
	*key = ft_substr(arg, 0, plus_eq - arg);
	handle_plus_equal(env_list, *key, plus_eq, value);
}
else if (equal_sign)
{
	*key = ft_substr(arg, 0, equal_sign - arg);
	*value = ft_strdup(equal_sign + 1);
}
else
{
	*key = ft_strdup(arg);
	*value = NULL;
}
if (!*key || (equal_sign && !*value))
	return (free(*key), free(*value), 0);
return (1);
}

void	handle_export(t_env **env_list, char *arg)
{
char	*key;
char	*value;

key = NULL;
value = NULL;
if (!arg || !*arg)
	return ;
if (!parse_export_argument(arg, &key, &value, env_list))
	return (perror("Minishell: memory allocation error"));
export_env_var(env_list, key, value);
}

void	export_env_var(t_env **env_list, char *key, char *value)
{
t_env	*temp;

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
		return (free(value), (void)0);
	}
	temp = temp->next;
}
add_env_var(env_list, key, value);
gc_track(key);
gc_track(value);
}