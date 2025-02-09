/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:10:48 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/02/09 18:30:23 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

static t_garbage_collector	**get_mem_list(void)
{
	static t_garbage_collector	*mem_list = NULL;

	return (&mem_list);
}
/**
 * @brief Allocates memory and tracks it in the garbage collection.
 * This function allocates memory and adds the pointer to a linked list
 * @param size the num of bytes to allocate.
 * @return void* Pointer to the allocated memory, Null on malloc failure.
 */
void	*gc_malloc(size_t size)
{
	t_garbage_collector	**mem_list;
	t_garbage_collector	*new_node;
	void				*ptr;

	ptr = malloc(size);
	if (!ptr)
		return (NULL);
	new_node = malloc(sizeof(t_garbage_collector));
	if (!new_node)
	{
		free(ptr);
		return (NULL);
	}
	mem_list = get_mem_list();
	new_node->ptr = ptr;
	new_node->next = *mem_list;
	*mem_list = new_node;
	return (ptr);
}

void	gc_track(void *ptr)
{
	t_garbage_collector	*new_node;
	t_garbage_collector	**mem_list;

	if (!ptr)
		return ;
	new_node = malloc(sizeof(t_garbage_collector));
	if (!new_node)
		return ;
	mem_list = get_mem_list();
	new_node->ptr = ptr;
	new_node->next = *mem_list;
	*mem_list = new_node;
}

void	gc_free_all(void)
{
	t_garbage_collector	**mem_list;
	t_garbage_collector	*current;
	t_garbage_collector	*temp;

	mem_list = get_mem_list();
	current = *mem_list;
	while (current)
	{
		free(current->ptr);
		temp = current;
		current = current->next;
		free(temp);
	}
	*mem_list = NULL;
}
