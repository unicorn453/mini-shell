/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 13:05:54 by kruseva           #+#    #+#             */
/*   Updated: 2025/03/15 13:52:53 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

int env_len(t_env **env_list)
{
    t_env *temp = *env_list;
    int i = 0;
    while(temp)
    {
        temp = temp->next;
        i++;
    }
    return i;
}

void print_env_reverse(t_env **env_list)
{
    if (!env_list || !*env_list)
        return;

    t_env *temp = *env_list;

    while (temp->next)
        temp = temp->next;

    while (temp)
    {
        // if(temp->value)
        printf("%s=%s\n", temp->key, temp->value);
        temp = temp->prev; 
    }
}
