/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:17:08 by kruseva           #+#    #+#             */
/*   Updated: 2025/04/10 19:57:17 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char	*remove_path(char *old_pwd)
{
	int		i;
	char	token;
	char	*ret_str;
	int		last;

	i = 0;
	token = '/';
	last = 0;
	while (old_pwd[i])
	{
		if (old_pwd[i] == token)
			last = i;
		i++;
	}
	ret_str = ft_substr(old_pwd, 0, last);
	gc_track(ret_str);
	return (ret_str);
}

static char	*get_new_pwd(t_cmd *cmd, t_env **env_list, char *old_pwd)
{
	char	*new_pwd;

	if (!cmd->cmd[1])
	{
		new_pwd = search_env_var(*env_list, "$HOME");
		if (!new_pwd)
		{
			return (NULL);
		}
	}
	else if (ft_strcmp(cmd->cmd[1], "..") == 0)
	{
		new_pwd = remove_path(old_pwd);
		if (!new_pwd)
		{
			return (NULL);
		}
	}
	else
		new_pwd = cmd->cmd[1];
	return (new_pwd);
}

static void	update_env_pwd(t_env **env_list, char *old_pwd)
{
	char	*test;
	char	*test2;
	char	*temp;

	test = ft_strjoin("OLDPWD=", old_pwd);
	handle_export(env_list, test);
	free(test);
	temp = getcwd(NULL, 0);
	test2 = ft_strjoin("PWD=", temp);
	handle_export(env_list, test2);
	free(temp);
	free(test2);
}

void	cd_test_call(t_cmd *cmd, t_env **env_list)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("getcwd"), (void)0);
	new_pwd = get_new_pwd(cmd, env_list, old_pwd);
	if (!new_pwd)
		return (free(old_pwd), (void)0);
	if (chdir(new_pwd) != 0)
		return (free(old_pwd), perror("cd"), (void)0);
	update_env_pwd(env_list, old_pwd);
	free(old_pwd);
}
