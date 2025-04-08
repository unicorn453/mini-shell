/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_variables.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:58:14 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/04/08 20:22:31 by dtrendaf         ###   ########.fr       */
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

void	add_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;

	new_node = create_env_node(key, value);
	if (!new_node)
		return ;
	if (*env_list)
	{
		(*env_list)->prev = new_node;
		new_node->next = *env_list;
	}
	*env_list = new_node;
}
typedef struct s_env_var
{
	char	*pwd;
	char	*shlvl;
	char	*temp;
	int		shlvl_value;
	int		i;

}t_env_var;
static int find_position(char *env_var,char **envp)
{
	int i = -1;
	while(envp[++i])
	{
		if (ft_strncmp(envp[i], env_var, ft_strlen(env_var)))
			return (i);
	}
	return (-1);
}
void	initialize_env_vars(t_env **env_list, char **envp)
{
	t_env_var stack;
	char *tempor;
	
	stack.i = -1;
	while (envp[++stack.i])
		handle_export(env_list, envp[stack.i]);
	stack.pwd = getcwd(NULL, 0);
	check(stack.pwd == NULL, 2);
	stack.shlvl = getenv("SHLVL");
	if (stack.shlvl == NULL)
		stack.shlvl_value = 1;
	else
		stack.shlvl_value = ft_atoi(stack.shlvl) + 1;
	stack.shlvl = ft_strjoin("SHLVL=", stack.temp = ft_itoa(stack.shlvl_value));
	tempor = ft_strdup(stack.shlvl);
	envp[find_position("SHLVL", envp)] = tempor;
	gc_track(tempor);
	gc_track(stack.temp);
	handle_export(env_list, stack.shlvl);
	free(stack.shlvl);
	stack.shlvl = ft_strjoin("PWD=", stack.pwd);
	handle_export(env_list, stack.shlvl);
	handle_export(env_list, "OLDPWD=NULL");
	free(stack.shlvl);
	free(stack.pwd);
}
