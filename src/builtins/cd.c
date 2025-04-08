/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:17:08 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/24 14:38:53 by dtrendaf         ###   ########.fr       */
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
	return (ret_str);
}

void	cd_test_call(t_cmd *cmd, t_env **env_list)
{
	char	*old_pwd;
	char	*new_pwd;
	char	*test;
	char	*test2;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (perror("getcwd"), (void)0);
	if (!cmd->cmd[1])
	{
		new_pwd = search_env_var(*env_list, "$HOME");
		if (!new_pwd)
			return (fprintf(stderr, "cd: HOME not set\n"), free(old_pwd),
				(void)0);
	}
	else if (strcmp(cmd->cmd[1], "..") == 0)
	{
		new_pwd = remove_path(old_pwd);
		if (!new_pwd)
			return (fprintf(stderr, "cd: OLDPWD not set\n"), free(old_pwd),
				(void)0);
	}
	else
		new_pwd = cmd->cmd[1];
	if (chdir(new_pwd) != 0)
		return (free(old_pwd), perror("cd"), (void)0);
	if (!new_pwd)
		return (free(old_pwd), perror("getcwd"), (void)0);
	test = ft_strjoin("OLDPWD=", old_pwd);
	handle_export(env_list, test);
	test2 = ft_strjoin("PWD=", getcwd(NULL, 0));
	handle_export(env_list, test2);
	free(old_pwd);
	free(test);
	free(test2);
}

// char *remove_path(char *old_pwd)
// {
//     int     i;
//     char    token;
//     char    *ret_str;
//     int     last;

//     i = 0;
//     token = '/';
//     last = 0;
//     while (old_pwd[i])
//     {
//         if (old_pwd[i] == token)
//             last = i;
//         i++;
//     }
//     ret_str = ft_substr(old_pwd, 0, last);
//     return (ret_str);
// }

// void    cd_test_call(t_cmd *cmd, t_env **env_list)
// {
//     char    *old_pwd;
//     char    *new_pwd;
//     char    *temp_pwd;
//     char    *test;
//     char    *test2;

//     old_pwd = getcwd(NULL, 0);
//     if (!old_pwd)
//         return(perror("getcwd"), (void)0);
    
//     if (!cmd->cmd[1])
//     {
//         new_pwd = search_env_var(*env_list, "$HOME");
//         if (!new_pwd)    
//             return(fprintf(stderr, "cd: HOME not set\n"), free(old_pwd), (void)0);
//     }
//     else if (strcmp(cmd->cmd[1], "..") == 0)
//     {
//         new_pwd = remove_path(old_pwd);
//         if (!new_pwd)
//             return(fprintf(stderr, "cd: error removing path\n"), free(old_pwd), (void)0);
//     }
//     else
//     {
//         new_pwd = strdup(cmd->cmd[1]);
//         if (!new_pwd)
//             return(fprintf(stderr, "cd: memory allocation error\n"), free(old_pwd), (void)0);
//     }
    
//     if (chdir(new_pwd) != 0)
//     {
//         free(new_pwd);
//         free(old_pwd);
//         return(perror("cd"), (void)0);
//     }
    
//     temp_pwd = getcwd(NULL, 0);
//     if (!temp_pwd)
//     {
//         free(new_pwd);
//         free(old_pwd);
//         return(perror("getcwd"), (void)0);
//     }
    
//     test = ft_strjoin("OLDPWD=", old_pwd);
//     if (test)
//         handle_export(env_list, test);
    
//     test2 = ft_strjoin("PWD=", temp_pwd);
//     if (test2)
//         handle_export(env_list, test2);
    
//     free(new_pwd);
//     free(old_pwd);
//     free(temp_pwd);
//     if (test)
//         free(test);
//     if (test2)
//         free(test2);
// }