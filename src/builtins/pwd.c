/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 09:53:45 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/04 11:04:41 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void get_pwd(void)
{
    char *pwd;
        pwd = getcwd(NULL, 0);
        if (!pwd)
            return (perror("Minishell: memory allocation error"));
        printf("%s\n", pwd);
    free(pwd);
}