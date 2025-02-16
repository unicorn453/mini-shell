/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:58:14 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/16 13:26:34 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = gc_malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (new_node->key == NULL)
		return (perror("Minishell: memory allocation error"), NULL);
	gc_track(new_node->key);
	if (value != NULL)
	{
		new_node->value = ft_strdup(value);
		if (new_node->value == NULL)
			return (perror("Minishell: memory allocation error"), NULL);
		gc_track(new_node->value);
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	new_node->next = *env_list;
	*env_list = new_node;
}

void	initialize_env_vars(t_env **env_list, char **envp)
{
	char *pwd;
	char *shlvl;

	pwd = getcwd(NULL, 0);
	shlvl = getenv("SHLVL");
	if (shlvl == NULL)
		shlvl = '1';
	else
		shlvl = ft_atoi(shlvl + 1);
	add_env_var(env_list, "PWD", pwd);
	add_env_var(env_list, "OLDPWD", NULL);
	add_env_var(env_list, "SHLVL", );

	free(pwd);
}