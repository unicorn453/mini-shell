/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 12:49:03 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/12 12:21:24 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"
void echo_call_check(t_cmd *cmd, t_env **env_list);

void	error(void)
{
	perror("\033[31mError");
	exit(EXIT_FAILURE);
}

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
		CHECK(path->temp == NULL, 1);
		path->full_path = ft_strjoin(path->temp, cmd);
		free(path->temp);
		CHECK(path->full_path == NULL, 1);
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

int check_builtins(t_env **env_list, t_cmd *cmd, char *command)
{
	(void)env_list;
	// char *builtins[] = {"echo", "cd", "pwd", "export", "unset", "env", "exit", NULL};
	// char *builtins[] = {"export", "pwd", "echo", NULL};
	char *builtins[] = {"export", "pwd", "echo", "/bin/echo", "cd", NULL};
	int i;
	i = 0;
	bool match = false;
	while(builtins[i])
	{
		if(strcmp(builtins[i], command) == 0)
		{
			match = true;
			cmd->builtin = true;
			break;
		}
		i++;
	}
	if (match)
	{
		if((ft_strncmp(builtins[i], "export", 6) == 0))
		{
			cmd->cmd[0] = "export";
		}
		else if ((ft_strncmp(builtins[i], "pwd", 3) == 0))
		{
			// get_pwd();
			cmd->cmd[0] = "pwd";
		}
		else if ((ft_strncmp(builtins[i], "echo", 4) == 0) || (ft_strncmp(builtins[i], "/bin/echo", 9) == 0))
		{
			cmd->cmd[0] = "echo";
		}
		else if ((ft_strncmp(builtins[i], "cd", 2) == 0))
		{
			cmd->cmd[0] = "cd";
		}
		// else if ((ft_strncmp(builtins[i], "exit", 4) == 0))
		// {
		// 	exit(0);
		// 	cmd->cmd[0] = "exit";
		// }
		// else if ((ft_strncmp(builtins[i], "unset", 5) == 0))
		// {
		// 	cmd->cmd[0] = "unset";
		// }
		// else if ((ft_strncmp(builtins[i], "env", 3) == 0))
		// {
		// 	cmd->cmd[0] = "env";
		// }
	}
	return (match);
}

char	*find_command_path(t_cmd *cmd_list, t_env **env_list, char *cmd, char **envp)
{
	t_path	*path;
	char	*ret_str;

	int check_built = check_builtins(env_list, cmd_list, cmd);
	if(check_built == 1)
		return (cmd);
	path = initialize_path();
	CHECK(path == NULL, 1);
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
	CHECK(path->path_env == NULL, 1);
	path->paths = ft_split(path->path_env, ':');
	CHECK(path->paths == NULL, 1);
	path->full_path = add_permission_free_path(path, cmd);
	if (path->full_path)
		return (path->full_path);
	return (free_paths(path, 0), ret_str = cmd, ret_str);
}
