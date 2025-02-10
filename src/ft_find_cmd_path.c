/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:49:03 by kruseva           #+#    #+#             */
/*   Updated: 2025/02/10 13:54:36 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

t_path	*initialize_path(void)
{
	t_path	*path;

	path = malloc(sizeof(t_path));
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
		if (!path->temp)
			return (free_paths(path, 0), path->full_path = NULL,
				path->full_path);
		path->full_path = ft_strjoin(path->temp, cmd);
		free(path->temp);
		if (!path->full_path)
			return (free_paths(path, 0), path->full_path);
		if (access(path->full_path, X_OK) == 0)
		{
			free_paths(path, 0);
			return (path->full_path);
		}
		unlink(path->full_path);
		free(path->full_path);
		path->full_path = NULL;
		path->i++;
	}
	return (NULL);
}

char	*find_command_path(char *cmd, char **envp)
{
	t_path	*path;
	char	*ret_str;

	path = initialize_path();
	if (!path)
		return (ret_str = NULL, ret_str);
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
	if (!path->path_env)
		return (free(path), ret_str = NULL, ret_str);
	path->paths = ft_split(path->path_env, ':');
	if (!path->paths)
		return (free(path), ret_str = NULL, ret_str);
	path->full_path = add_permission_free_path(path, cmd);
	if (path->full_path)
		return (path->full_path);
	return (free_paths(path, 0), free(path), ret_str = NULL, ret_str);
}
