/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kruseva <kruseva@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:41:19 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/11 15:22:20 by kruseva          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	int		exit_status = 0;
	
	env_list = NULL;
	initialize_env_vars(&env_list, envp);
	(void)argc;
	(void)argv;
	main_loop(envp, &env_list);
	gc_free_all();
	return (exit_status);
}