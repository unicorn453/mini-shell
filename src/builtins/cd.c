/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 12:17:08 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/12 18:14:41 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

char *remove_path(char *old_pwd)
{
    int i = 0;

    char token = '/';
    char *ret_str;
    int last = 0;
    while(old_pwd[i])
    {
        if(old_pwd[i] == token)
        last = i;
    i++;
    }
    ret_str = ft_substr(old_pwd, 0, last);
    return ret_str;
}

void cd_test_call(t_cmd *cmd, t_env **env_list)
{
    char *old_pwd;
    char *new_pwd;

    old_pwd = getcwd(NULL, 0);
    if (!old_pwd) {
        perror("getcwd");
        return;
    }

    if (!cmd->cmd[1]) {
        new_pwd = search_env_var(*env_list, "$HOME");
        if (!new_pwd) {
            fprintf(stderr, "cd: HOME not set\n");
            free(old_pwd);
            return;
        }
    } 
    else if (strcmp(cmd->cmd[1], "..") == 0) {
        new_pwd = remove_path(old_pwd);
        if (!new_pwd) {
            fprintf(stderr, "cd: OLDPWD not set\n");
            free(old_pwd);
            return;
        }
    } 
    else {
        new_pwd = cmd->cmd[1];
    }

    if (chdir(new_pwd) != 0) {
        perror("cd");
        free(old_pwd);
        return;
    }

    // char *updated_pwd = getcwd(NULL, 0);
    if (!new_pwd) {
        perror("getcwd");
        free(old_pwd);
        return;
    }

   
    remove_env_var(env_list, "OLDPWD"); 
    remove_env_var(env_list, "PWD");
    
    add_env_var(env_list, "OLDPWD", old_pwd);
    add_env_var(env_list, "PWD", new_pwd);

    free(old_pwd);
    free(new_pwd);
}
