/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:00:37 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/15 13:58:30 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void remove_env_var(t_env **env_list, char *key)
{
    t_env *curr = *env_list;

    while (curr)
    {
        if (ft_strncmp(curr->key, key, ft_strlen(key) + 1) == 0)
        {
            if (curr == *env_list)
                *env_list = curr->next;

            if (curr->next)
                curr->next->prev = curr->prev;

            if (curr->prev)
                curr->prev->next = curr->next;

            gc_untrack(curr->key);
            gc_untrack(curr->value);
            gc_untrack(curr);
            
            return;
        }
        curr = curr->next;
    }
}
