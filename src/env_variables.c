/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:58:14 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/15 13:31:24 by kruseva          ###   ########.fr       */
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
	new_node->prev = NULL;
	return (new_node);
}

void add_env_var(t_env **env_list, char *key, char *value)
{
    t_env *new_node;

	new_node = create_env_node(key, value);
    if (!new_node)
        return;

    if (*env_list) // If the list is not empty, set the previous pointer
    {
        (*env_list)->prev = new_node;
        new_node->next = *env_list;
    }

    *env_list = new_node; // Update head pointer
}

void	initialize_env_vars(t_env **env_list, char **envp) 
{
	char 	*pwd;
	char	*shlvl;
	int		shlvl_value;
	int	i;

	i = -1;
	while (envp[++i])
		handle_export(env_list, envp[i]);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("Minishell: getcwd error");
		return;
	}
	shlvl = getenv("SHLVL");
	if (shlvl == NULL)
		shlvl_value = 1;
	else
		shlvl_value = ft_atoi(shlvl) + 1;
	shlvl = ft_itoa(shlvl_value);
	add_env_var(env_list, "SHLVL", shlvl);
	add_env_var(env_list, "PWD", pwd);
	add_env_var(env_list, "OLDPWD", NULL);
	free(pwd);
}

