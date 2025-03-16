/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtrendaf <dtrendaf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 17:41:19 by dtrendaf          #+#    #+#             */
/*   Updated: 2025/03/16 17:20:31 by dtrendaf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_shell.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env_list;
	int		exit_status = 0;
	
	env_list = NULL;
	initialize_env_vars(&env_list, envp);
	setup_interactive_signals();
	(void)argc;
	(void)argv;
	main_loop(envp, &env_list);
	// gc_free_all();
	return (exit_status);
}