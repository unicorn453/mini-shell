/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:49:03 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/09 23:16:58 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

t_path	*initialize_path(void)
{
	t_path	*path;

	path = gc_malloc(sizeof(t_path));
	if (!path)
	{
		path = NULL;
		return (path);
	}
	path->path_env = NULL;
	path->paths = NULL;
	path->full_path = NULL;
	path->i = 0;
	path->temp = NULL;
	return (path);
}

void	free_paths(t_path *path, int error_bool)
{
	int	j;

	j = 0;
	if (!path || !path->paths)
		return ;
	while (path->paths[j])
	{
		free(path->paths[j]);
		path->paths[j] = NULL;
		j++;
	}
	free(path->paths);
	path->paths = NULL;
	if (error_bool)
		error();
}

char	*add_permission_free_path(t_path *path, char *cmd)
{
	path->i = 0;
	while (path->paths[path->i])
	{
		path->temp = ft_strjoin(path->paths[path->i], "/");
		check(path->temp == NULL, 1);
		path->full_path = ft_strjoin(path->temp, cmd);
		gc_track(path->full_path);
		free(path->temp);
		check(path->full_path == NULL, 1);
		if (access(path->full_path, X_OK) == 0)
		{
			free_paths(path, 0);
			return (path->full_path);
		}
		if (path->full_path)
			unlink(path->full_path);
		path->full_path = NULL;
		path->i++;
	}
	return (NULL);
}

static int	is_builtin_or_special(t_cmd *cmd_list, t_env **env_list, char *cmd)
{
	int	check_built;
	int	check_special_built;

	cmd_list->env_list = env_list;
	check_built = check_builtins(cmd_list, cmd);
	check_special_built = check_speacial_builtins(cmd_list, cmd);
	return (check_built == 1 || check_special_built == 1);
}

char	*find_command_path(t_cmd *cmd_list, t_env **env_list, char *cmd,
		char **envp)
{
	t_path	*path;
	char	*ret_str;

	if (is_builtin_or_special(cmd_list, env_list, cmd))
		return (cmd);
	path = initialize_path();
	check(path == NULL, 1);
	path->i = 0;
	while (envp[path->i])
	{
		if (ft_strncmp(envp[path->i], "PATH=", 5) == 0)
		{
			path->path_env = envp[path->i] + 5;
			break ;
		}
		path->i++;
	}
	if (path->path_env == NULL)
		return (cmd);
	check(path->path_env == NULL, 1);
	path->paths = ft_split(path->path_env, ':');
	check(path->paths == NULL, 1);
	path->full_path = add_permission_free_path(path, cmd);
	if (path->full_path)
		return (path->full_path);
	return (free_paths(path, 0), ret_str = cmd, ret_str);
}
