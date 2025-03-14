/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 15:00:37 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/13 10:25:27 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini_shell.h"

void remove_env_var(t_env **env_list, char *key)
{
    t_env *temp = NULL;
    t_env *prev = NULL;
    t_env *curr = *env_list;

    while (curr)
    {
        if (ft_strncmp(curr->key, key, ft_strlen(key)) == 0)
        {
            temp = curr;
            if (prev)
                prev->next = curr->next;  // Skip the node being removed
            else
                *env_list = curr->next; // Update head if first node is removed

            gc_untrack(temp->key);
            gc_untrack(temp->value);
            gc_untrack(temp);
			if (prev)
			curr = prev->next;
			else
			curr = *env_list;
        }
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}