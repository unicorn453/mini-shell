/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 21:10:48 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/18 19:47:04 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

void cleanup_readline(void)
{
    clear_history();  // Frees history entries
    rl_clear_history();  // Ensures further cleanup
}

t_garbage_collector	**get_mem_list(void)
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
	t_garbage_collector	*current;
	t_garbage_collector	*new_node;
	t_garbage_collector	**mem_list;

	if (!ptr)
		return ;
	mem_list = get_mem_list();
	current = *mem_list;
	while (current)
	{
		if (current->ptr == ptr)
			return ; // Avoid duplicate tracking
		current = current->next;
	}
	new_node = malloc(sizeof(t_garbage_collector));
	if (!new_node)
		return ;
	new_node->ptr = ptr;
	new_node->next = *mem_list;
	*mem_list = new_node;
}

// void	gc_free_all(void)
// {
// 	t_garbage_collector	**mem_list;
// 	t_garbage_collector	*current;
// 	t_garbage_collector	*temp;

// 	mem_list = get_mem_list();
// 	current = *mem_list;
// 	while (current)
// 	{
// 		free(current->ptr);
// 		temp = current;
// 		current = current->next;
// 		free(temp);
// 	}
// 	*mem_list = NULL;
// }
void close_open_fds(void)
{
    int fd;
	fd = 3;
	while (fd < 10240)
	{
		close(fd);
		fd++;
	}
}

void	gc_free_all(void)
{
	t_garbage_collector	**mem_list;
	t_garbage_collector	*current;
	t_garbage_collector	*temp;

	mem_list = get_mem_list();
	if (!mem_list || !*mem_list) // Check if the list itself is NULL
		return ;
	current = *mem_list;
	while (current)
	{
		free(current->ptr);
		current->ptr = NULL;
		temp = current;
		current = current->next;
		free(temp);
	}
	close_open_fds();
	cleanup_readline();
	*mem_list = NULL;
}

void	gc_untrack(void *ptr)
{
	t_garbage_collector	**mem_list;
	t_garbage_collector	*current;
	t_garbage_collector	*prev;

	if (!ptr)
		return ;
	mem_list = get_mem_list();
	current = *mem_list;
	prev = NULL;
	while (current)
	{
		if (current->ptr == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				*mem_list = current->next;
			free(current->ptr);
			current->ptr = NULL;
			free(current);
			current = NULL;
			return ;
		}
		prev = current;
		current = current->next;
	}
}
